import cv2
import mediapipe as mp
import numpy as np
import csv
import os

# MediaPipeの標準描画ユーティリティと手の接続情報
mp_drawing = mp.solutions.drawing_utils
mp_hands = mp.solutions.hands

# ▼▼▼ 必須のインポート ▼▼▼
from mediapipe.framework.formats import landmark_pb2
# ▲▲▲ 必須のインポート ▲▲▲


# --- 定数 ---
MATCH_THRESHOLD = 0.1

def _get_centroid(landmarks):
    """(変更なし)"""
    x_coords = [lm.x for lm in landmarks]
    y_coords = [lm.y for lm in landmarks]
    return np.mean(x_coords), np.mean(y_coords)

def _get_distance(p1, p2):
    """(変更なし)"""
    return np.sqrt((p1[0] - p2[0])**2 + (p1[1] - p2[1])**2)

def match_hand_ids(current_landmarks_list, hand_ids_state, next_id):
    """(変更なし)"""
    
    current_centroids = {idx: _get_centroid(landmarks) for idx, landmarks in enumerate(current_landmarks_list)}
    
    matched_idx_to_id = {}
    updated_hand_ids_state = {}
    used_old_ids = set()
    unmatched_current_indices = []

    # 1. マッチングフェーズ
    for idx, current_centroid in current_centroids.items():
        best_match_id = -1
        min_dist = float('inf')
        
        for old_id, old_centroid in hand_ids_state.items():
            dist = _get_distance(current_centroid, old_centroid)
            if dist < min_dist and dist < MATCH_THRESHOLD:
                min_dist = dist
                best_match_id = old_id
        
        if best_match_id != -1 and best_match_id not in used_old_ids:
            matched_idx_to_id[idx] = best_match_id
            updated_hand_ids_state[best_match_id] = current_centroid
            used_old_ids.add(best_match_id)
        else:
            unmatched_current_indices.append(idx)

    # 2. 新規ID割り当てフェーズ
    for idx in unmatched_current_indices:
        new_id = next_id
        matched_idx_to_id[idx] = new_id
        updated_hand_ids_state[new_id] = current_centroids[idx]
        next_id += 1
        
    return matched_idx_to_id, updated_hand_ids_state, next_id


# ▼▼▼ この関数全体を置き換えてください ▼▼▼
def draw_hand_landmarks(image, hand_landmarks, hand_id, handedness, gesture, gesture_score):
    """
    画像に手のランドマークと関連情報を描画する。
    (GestureRecognizerタスクの [List[NormalizedLandmark]] 形式に対応)
    """
    
    # 描画ライブラリ(mp_drawing)が要求する Protobuf 形式 (NormalizedLandmarkList) を準備
    hand_landmarks_proto = landmark_pb2.NormalizedLandmarkList()
    
    # === ↓↓↓ ここが重要 ↓↓↓ ===
    # 'hand_landmarks' (Pythonオブジェクトのリスト) から
    # データを1つずつ取り出し、Protobufオブジェクトに変換して 'hand_landmarks_proto' に追加する
    for py_landmark in hand_landmarks:
        # 新しい Protobuf ランドマークオブジェクトを作成し、データをコピー
        hand_landmarks_proto.landmark.add(
            x=py_landmark.x,
            y=py_landmark.y,
            z=py_landmark.z,
            visibility=py_landmark.visibility,
            presence=py_landmark.presence
        )
    # === ↑↑↑ 修正完了 ↑↑↑ ===

    # ランドマークと接続線の描画
    mp_drawing.draw_landmarks(
        image,
        hand_landmarks_proto,  # 変換後の Protobuf オブジェクトを使用
        mp_hands.HAND_CONNECTIONS,
        mp_drawing.DrawingSpec(color=(121, 22, 76), thickness=2, circle_radius=4),
        mp_drawing.DrawingSpec(color=(250, 44, 250), thickness=2, circle_radius=2),
    )
    
    # (以下のテキスト描画処理は前回の修正のままでOK)
    h, w, _ = image.shape
    x_coords = [lm.x * w for lm in hand_landmarks]
    y_coords = [lm.y * h for lm in hand_landmarks]
    
    # 手首 (landmark 0) の位置を取得
    x_wrist = int(hand_landmarks[0].x * w)
    y_wrist = int(hand_landmarks[0].y * h)
    
    # テキストの色
    color = (0, 0, 255) if handedness == 'Right' else (255, 0, 0)
    
    # 情報をテキストで描画
    text_lines = [
        f"ID: {hand_id} ({handedness})",
        f"Gesture: {gesture}",
        f"Score: {gesture_score:.2f}"
    ]
    
    for i, line in enumerate(text_lines):
        cv2.putText(image, line,
                    (x_wrist - 30, y_wrist + 30 + (i * 30)),
                    cv2.FONT_HERSHEY_SIMPLEX, 
                    0.8, color, 2)
                    
    return image
# ▲▲▲ この関数全体を置き換えてください ▲▲▲


def save_gesture_data_to_csv(data_rows, file_path):
    """(変更なし)"""
    
    header = ['Hand_ID', 'Handedness', 'Timestamp', 'Gesture', 'Gesture_Score']
    for i in range(21):
        header.extend([f'Landmark_{i}_x', f'Landmark_{i}_y', f'Landmark_{i}_z'])
        
    try:
        os.makedirs(os.path.dirname(file_path), exist_ok=True)
        
        with open(file_path, mode='w', newline='', encoding='utf-8') as f:
            writer = csv.writer(f)
            writer.writerow(header)
            writer.writerows(data_rows)
        print(f"データを保存しました: {file_path}")
        
    except Exception as e:
        print(f"CSVファイルの保存中にエラーが発生しました: {e}")