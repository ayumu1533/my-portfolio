import pygame
import multiprocessing
import os
import sys
import time

# Windows/macOSで安全にプロセスを開始するためのおまじない
try:
    multiprocessing.set_start_method('spawn')
except RuntimeError:
    pass

# スクリプトのディレクトリをパスに追加（インポートエラー対策）
sys.path.append(os.path.dirname(__file__))

try:
    # 子プロセスに必要なインポートだけをここに残す
    from source.gesture_processor import run_hand_tracking
except ImportError as e:
    print(f"インポートエラー: {e}")
    print("gesture_processor.py が main.py と同じディレクトリにあることを確認してください。")
    sys.exit(1)


if __name__ == "__main__":

    # === ★★★ 修正点 ★★★ ===
    # calculate_percent (Pygame) のインポートを
    # if __name__ == "__main__": のブロック内に移動する
    try:
        from source.game import start_screen 
    except ImportError as e:
        print(f"インポートエラー: {e}")
        print("calculate_percent.py が main.py と同じディレクトリにあることを確認してください。")
        sys.exit(1)
    except pygame.error as e:
        print(f"Pygameの初期化中にエラーが発生しました: {e}")
        print("子プロセスがPygameをインポートしようとした可能性があります。この修正で解決するはずです。")
        sys.exit(1)
    # === ★★★ 修正完了 ★★★ ===


    print("アプリケーションを起動します...")
    
    # プロセス間通信用のQueueを作成
    gesture_queue = multiprocessing.Queue()

    # --- プロセス1: ハンドトラッキングを開始 ---
    tracking_process = multiprocessing.Process(
        target=run_hand_tracking, 
        args=(gesture_queue,)
    )
    time.sleep(3)
    tracking_process.daemon = True # メインプロセス終了時に自動で閉じる
    tracking_process.start()

    print("ハンドトラッキングプロセスを開始しました。(PID: {})".format(tracking_process.pid))
    print("ゲームウィンドウが起動します...")

    # --- メインプロセス: Pygameゲームを開始 ---
    try:
        # この start_screen はメインプロセスでのみ実行される
        start_screen(gesture_queue=gesture_queue)
    except KeyboardInterrupt:
        print("\nゲームが中断されました。")
    except Exception as e:
        print(f"\nゲーム実行中に予期せぬエラーが発生しました: {e}")
    finally:
        # --- クリーンアップ ---
        print("クリーンアップ中...")
        if tracking_process.is_alive():
            tracking_process.terminate() # ハンドトラッキングプロセスを強制終了
            tracking_process.join()
        print("終了しました。")
        sys.exit(0)