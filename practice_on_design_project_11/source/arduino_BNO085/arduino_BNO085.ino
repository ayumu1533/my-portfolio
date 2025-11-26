#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <Wire.h>

// ==========================================
// 設定エリア
// ==========================================
// 何ミリ秒間隔の連打まで許容するか（これより速い連打は無視）
// 貧乏ゆすりの速さに合わせて調整してください。
// 100ms = 0.1秒。ここを大きくすると誤反応が減りますが、高速連打に追いつかなくなります。
const long COOL_TIME_MS = 200; 

// 反応する強さの閾値（LINEAR_ACCELERATIONなので0が基準）
// 軽く反応しすぎる場合は、ここを 3.0 -> 5.0 と大きくしてください。
const float ACCEL_THRESH = 3.0; 
// ==========================================

enum MODE {
  FAST_MODE = 0,          
  NORMAL_MODE = 1,        
  FAST_MODE_EULAR = 2,    
  NORMAL_MODE_EULAR = 3,  
  ACCEL_MODE = 4,         
  GYRO_MODE = 5,          
  MAGNE_MODE = 6          
};

int sensor_mode = MODE::ACCEL_MODE;

#define BNO08X_RESET -1

struct euler_t {
  float yaw;
  float pitch;
  float roll;
} ypr;

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;
sh2_SensorId_t reportType;
long reportIntervalUs;

// クールダウン管理用変数
unsigned long last_trigger_time = 0;

void setReports(sh2_SensorId_t reportType, long report_interval) {
  Serial.println("Setting desired reports");
  if (! bno08x.enableReport(reportType, report_interval)) {
    Serial.println("Could not enable stabilized remote vector");
  }
}

void set_mode(int mode){
  switch (mode) {
    // ... (他のモードは省略、変更なし) ...
    case MODE::FAST_MODE: reportType = SH2_GYRO_INTEGRATED_RV; reportIntervalUs = 2000; break;
    case MODE::NORMAL_MODE: reportType = SH2_ARVR_STABILIZED_RV; reportIntervalUs = 5000; break;
    case MODE::FAST_MODE_EULAR: reportType = SH2_GYRO_INTEGRATED_RV; reportIntervalUs = 2000; break;
    case MODE::NORMAL_MODE_EULAR: reportType = SH2_ARVR_STABILIZED_RV; reportIntervalUs = 5000; break;
    
    case MODE::ACCEL_MODE:
      // ★ここが重要です
      // SH2_LINEAR_ACCELERATION = 重力除去済みの加速度
      // SH2_ACCELEROMETER       = 重力込みの加速度
      reportType = SH2_LINEAR_ACCELERATION; 
      reportIntervalUs = 2000; 
      break;

    case MODE::GYRO_MODE: reportType = SH2_GYROSCOPE_CALIBRATED; reportIntervalUs = 2000; break;
    case MODE::MAGNE_MODE: reportType = SH2_MAGNETIC_FIELD_CALIBRATED; reportIntervalUs = 2000; break;
    default: break;
  }
}

void setup(void) {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println("Adafruit BNO08x test!");

  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");

  set_mode(sensor_mode);
  setReports(reportType, reportIntervalUs);

  Serial.println("Reading events");
  delay(100);
}

// ... (Quaternion変換関数などは省略、変更なし) ...
void quaternionToEuler(float qr, float qi, float qj, float qk, euler_t* ypr, bool degrees = false) {
    float sqr = sq(qr);
    float sqi = sq(qi);
    float sqj = sq(qj);
    float sqk = sq(qk);
    ypr->yaw = atan2(2.0 * (qi * qj + qk * qr), (sqi - sqj - sqk + sqr));
    ypr->pitch = asin(-2.0 * (qi * qk - qj * qr) / (sqi + sqj + sqk + sqr));
    ypr->roll = atan2(2.0 * (qj * qk + qi * qr), (-sqi - sqj + sqk + sqr));
    if (degrees) { ypr->yaw *= RAD_TO_DEG; ypr->pitch *= RAD_TO_DEG; ypr->roll *= RAD_TO_DEG; }
}
void quaternionToEulerRV(sh2_RotationVectorWAcc_t* rotational_vector, euler_t* ypr, bool degrees = false) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}
void quaternionToEulerGI(sh2_GyroIntegratedRV_t* rotational_vector, euler_t* ypr, bool degrees = false) {
    quaternionToEuler(rotational_vector->real, rotational_vector->i, rotational_vector->j, rotational_vector->k, ypr, degrees);
}

void process_sensor_data(){
    switch (sensor_mode) {
      // ... (他のモード出力は変更なし) ...
      case MODE::FAST_MODE:
      case MODE::NORMAL_MODE:
        // 省略
        break;
      case MODE::FAST_MODE_EULAR:
      case MODE::NORMAL_MODE_EULAR:
        // 省略
        break;

      case MODE::ACCEL_MODE: {
        // LINEAR_ACCELERATION (重力除去済み) を取得
        float lx = sensorValue.un.linearAcceleration.x;
        float ly = sensorValue.un.linearAcceleration.y;
        float lz = sensorValue.un.linearAcceleration.z;

        // 現在の時刻を取得
        unsigned long now_ms = millis();

        // 1. クールダウンタイムが経過しているか？
        // 2. 加速度が閾値を超えているか？ (lzは上方向の加速度)
        if ((now_ms - last_trigger_time > COOL_TIME_MS) && (lz > ACCEL_THRESH)) {
          
          Serial.println("1");
          
          // トリガー時刻を更新（ここからまたCOOL_TIME_MSの間は反応しない）
          last_trigger_time = now_ms;
        }
        break;
      }

      case MODE::GYRO_MODE:
        // 省略
        break;
      case MODE::MAGNE_MODE:
        // 省略
        break;
      default: break;
    }
}

bool is_streaming = false;

void loop() {
  if (bno08x.wasReset()) {
    setReports(reportType, reportIntervalUs);
  }

  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim(); 
    if (command == "START") { is_streaming = true; Serial.println("OK"); } 
    else if (command == "STOP") { is_streaming = false; Serial.println("OK"); }
    else if (command == "READ") {
      if (bno08x.getSensorEvent(&sensorValue)){ process_sensor_data(); }
      Serial.println("OK");
    }
  }

  // ストリーミングかつデータがあれば処理
  if (is_streaming){
    if (bno08x.getSensorEvent(&sensorValue)) {
      process_sensor_data();
    }
  }
}