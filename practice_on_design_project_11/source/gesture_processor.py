"""
MediaPipeを使用した手指追跡（Hand Tracking）とジェスチャー認識プログラム
（マルチプロセス配信用に改造）

このプログラムは、MediaPipeのGesture Recognizerモデルを使用して、
カメラからのビデオストリームから手のランドマーク（特徴点）を検出し、
ジェスチャーを認識して、Queue経由でメインプロセス（ゲーム）に送信します。
"""

import cv2
import mediapipe as mp
import numpy as np
import os
from datetime import datetime

# 元のコードに handtracking_util があったため、デバッグ描画用に一部インポート
# このファイルがない場合は、draw_hand_landmarks と match_hand_ids の呼び出しをコメントアウトしてください。
try:
    from source.handtracking_util import match_hand_ids, draw_hand_landmarks
    HAND_UTIL_LOADED = True
except ImportError:
    print("Warning: handtracking_util.py が見つかりません。デバッグ描画の一部がスキップされます。")
    HAND_UTIL_LOADED = False


# モデルパスはご自身の環境に合わせて修正してください
root_dir = os.path.dirname("C:/practice_on_design_project_11/") 
model_path = os.path.join(root_dir, "rsc", "models", "gesture_recognizer.task")
if not os.path.exists(model_path):
    print(f"エラー: モデルファイルが見つかりません: {model_path}")
    print("スクリプト内の 'model_path' を正しいパスに修正してください。")
    # 代替パス（例）
    # model_path = "gesture_recognizer.task" 
    # print(f"代替パス {model_path} を試行します...")


def run_hand_tracking(gesture_queue):
    """MediaPipeのGesture Recognizerを使用して手のランドマークとジェスチャーを検出し、Queueに送信する"""
    
    # MediaPipe Gesture Recognizerの初期化
    mp_gesture_recognizer = mp.tasks.vision.GestureRecognizer
    
    hand_state = {"Left": False, "Right": False}

    # 実行オプションの設定
    options = mp.tasks.vision.GestureRecognizerOptions(
        base_options=mp.tasks.BaseOptions(model_asset_path=model_path),
        running_mode=mp.tasks.vision.RunningMode.VIDEO,
        num_hands=2  # 両手を検出するように設定
    )
    
    # カメラの初期化
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("エラー: カメラを開けませんでした。")
        return

    # 手IDの追跡用辞書
    hand_ids = {}
    next_id = 0
    
    # Gesture Recognizerの作成
    try:
        with mp_gesture_recognizer.create_from_options(options) as recognizer:
            while cap.isOpened():
                success, image = cap.read()
                if not success:
                    print("カメラからのフレーム取得に失敗しました。")
                    break
                
                # 画像の前処理
                image = cv2.flip(image, 1)  # 水平方向に反転（自撮りビュー）
                image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
                mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=image_rgb)
                
                # 現在のタイムスタンプ（ミリ秒）
                timestamp_ms = int(cv2.getTickCount() / cv2.getTickFrequency() * 1000)
                
                # 手のランドマークとジェスチャー検出
                detection_result = recognizer.recognize_for_video(mp_image, timestamp_ms)
                
                # === ジェスチャーデータ送信処理 ===

                # 各手の現在ジェスチャー
                current_gestures = {'Left': 'None', 'Right': 'None'}

                # --- New! グー連続制限のための状態 ---
                # hand_state = {"Left": False, "Right": False}
                # ↑ これは run_hand_tracking の先頭で一度だけ定義してね
                # hand_state[hand] = True のとき「その手はグーを送信済み」

                if detection_result.handedness:
                    for i, hand in enumerate(detection_result.handedness):

                        hand_name = hand[0].category_name  # 'Left' or 'Right'
                        gesture_name = 'None'

                        # ジェスチャーが検出されている場合のみ取得
                        if detection_result.gestures and i < len(detection_result.gestures):
                            if detection_result.gestures[i]:
                                gesture_name = detection_result.gestures[i][0].category_name

                        if gesture_name == "Closed_Fist":  # MediaPipe の「グー」
                            current_gestures[hand_name] = "Closed_Fist"

                        elif gesture_name == "Open_Palm":  # MediaPipe の「パー」
                            # パーが来たらリセット
                            current_gestures[hand_name] = "Open_Palm"

                        else:
                            # その他（ピースなど）は普通に流す
                            current_gestures[hand_name] = gesture_name

                # Queue 送信（最新のみ残す）
                try:
                    while not gesture_queue.empty():
                        gesture_queue.get_nowait()
                    gesture_queue.put_nowait(current_gestures)
                except:
                    pass

                # === 送信処理ここまで ===


                # === デバッグ用描画処理 ===
                if HAND_UTIL_LOADED:
                    # 既存の手IDと新しく検出された手をマッチング
                    matched_ids, hand_ids, next_id = match_hand_ids(
                        detection_result.hand_landmarks if detection_result.hand_landmarks else [],
                        hand_ids,
                        next_id
                    )

                if detection_result.hand_landmarks:
                    for hand_idx, hand_landmarks in enumerate(detection_result.hand_landmarks):
                        
                        if HAND_UTIL_LOADED:
                            hand_id = matched_ids.get(hand_idx, -1)
                            handedness = detection_result.handedness[hand_idx][0].category_name
                            gesture = current_gestures.get(handedness, "None")
                            gesture_score = 0.0
                            if detection_result.gestures and hand_idx < len(detection_result.gestures):
                                if detection_result.gestures[hand_idx]:
                                    gesture_score = detection_result.gestures[hand_idx][0].score
                            
                            # ランドマークの描画
                            image = draw_hand_landmarks(image, hand_landmarks, hand_id, handedness, gesture, gesture_score)

                # 画像の表示 (デバッグが不要ならこのブロック全体を削除)
                cv2.putText(image, f"Sending: {current_gestures}", (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)
                cv2.imshow('Gesture Processor (Debug Window)', image)
                
                # 'q' で終了
                if cv2.waitKey(5) & 0xFF == ord('q'):
                    break
    
    except Exception as e:
        print(f"MediaPipeの実行中にエラーが発生しました: {e}")
        print("モデルパスが正しいか、カメラが接続されているか確認してください。")

    # リソースの解放
    cap.release()
    cv2.destroyAllWindows()
    print("ジェスチャープロセッサを終了します。")

# このファイルは main.py からインポートされるため、
# if __name__ == "__main__": ブロックは削除します。