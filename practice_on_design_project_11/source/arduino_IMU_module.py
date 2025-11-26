import serial
import time
import argparse

class ArduinoIMUModule:
    def __init__(self, port: str = 'COM3', baudrate: int = 115200):
        self.port = port
        self.baudrate = baudrate
        self.serial = None
        self.is_connected = False
        self.is_streaming = False

    def connect(self) -> bool:
        try:
            self.serial = serial.Serial(
                port=self.port,
                baudrate=self.baudrate,
                timeout=1.0
            )
            self.is_connected = True
            print(f"{self.port} に接続しました")
            return True
        except serial.SerialException as e:
            print(f"接続エラー: {e}")
            return False

    def disconnect(self):
        if self.serial and self.serial.is_open:
            self.serial.close()
            self.is_connected = False
            print(f"{self.port} を切断しました")

    def start_streaming(self) -> bool:
        if not self.is_connected:
            print("接続が確立されていません")
            return False
        self.serial.write(b'START\n')
        time.sleep(0.1)
        response = self.serial.readline().decode().strip()
        if response == 'OK':
            self.is_streaming = True
            print(f"{self.port} ストリーミング開始")
            return True
        return False

    def stop_streaming(self) -> bool:
        if not self.is_connected or not self.is_streaming:
            return False
        self.serial.write(b'STOP\n')
        time.sleep(0.1)
        response = self.serial.readline().decode().strip()
        if response == 'OK':
            self.is_streaming = False
            print(f"{self.port} ストリーミング停止")
            return True
        return False

    def read_sensor_data(self):
        if not self.is_connected or self.serial.in_waiting == 0:
            return None
        try:
                if self.serial.in_waiting > 0:
                    line = self.serial.readline().decode().strip()
                    return line  # "1" や "2" が返る想定
        except Exception as e:
            print(f"{self.port} センサーデータ読み取りエラー: {e}")
            return None


if __name__ == "__main__":
    # ===============================
    #  引数の設定
    # ===============================
    parser = argparse.ArgumentParser(description='2つのIMUモジュールを読み取る')
    parser.add_argument('--right', type=str, default='3', help='右足のCOMポート番号')
    parser.add_argument('--left', type=str, default='4', help='左足のCOMポート番号')
    args = parser.parse_args()

    # ===============================
    #  IMU モジュールの作成
    # ===============================
    imu_right = ArduinoIMUModule(port=f'COM{args.right}')
    imu_left = ArduinoIMUModule(port=f'COM{args.left}')

    if not imu_right.connect() or not imu_left.connect():
        exit()

    imu_right.start_streaming()
    imu_left.start_streaming()

    try:
        while True:
            data_right = imu_right.read_sensor_data()
            data_left = imu_left.read_sensor_data()

            leg_right_active = data_right == "1"
            leg_left_active = data_left == "2"

            if leg_right_active:
                print("右足アクティブ")
            if leg_left_active:
                print("左足アクティブ")

            time.sleep(0.01)
    except KeyboardInterrupt:
        print("\nプログラムを終了します")
    finally:
        imu_right.stop_streaming()
        imu_left.stop_streaming()
        imu_right.disconnect()
        imu_left.disconnect()
