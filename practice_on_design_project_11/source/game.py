# calculate_percent_ui_chart_ver.py
import pygame
import random
import argparse
import os
import json
import multiprocessing

# === IMU判定追加部分 ===
# 左右ジェスチャーラッチタイマーとKB入力の後
from arduino_IMU_module import ArduinoIMUModule

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

pygame.init()
pygame.mixer.init()

# === 画面設定 ===
# (変更なし...省略)
WIDTH, HEIGHT = 1200, 700
screen = pygame.display.set_mode((WIDTH, HEIGHT), pygame.DOUBLEBUF)
pygame.display.set_caption("3D風リズムゲーム（ジェスチャー対応版）")
clock = pygame.time.Clock()
DATA_PATH = os.path.dirname(__file__)

# === 音声・画像読み込み ===
# (変更なし...省略)
VOICE_READYQ = os.path.join(DATA_PATH, "rsc/「準備はいいですか？」.mp3")
VOICE_LADY = os.path.join(DATA_PATH, "rsc/「レディー…」.mp3")
VOICE_GO = os.path.join(DATA_PATH, "rsc/「ゴー」.mp3")
START_BGM = os.path.join(DATA_PATH, "rsc/Starlight_Dreams.mp3")
try:
    gigibaba_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/gigibaba.png")).convert_alpha()
    hand_left_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/g10-1.png")).convert_alpha()
    hand_left_2_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/hand_right_2.png")).convert_alpha()
    hand_right_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/g10.png")).convert_alpha()
    hand_right_2_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/hand_left_2.png")).convert_alpha()
    leg_left_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/g10-3.png")).convert_alpha()
    leg_left_2_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/leg_left_2.png")).convert_alpha()
    leg_right_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/g10-2.png")).convert_alpha()
    leg_right_2_img = pygame.image.load(os.path.join(DATA_PATH, "rsc/leg_right_2.png")).convert_alpha()
    btn_normal = pygame.image.load(os.path.join(DATA_PATH, "rsc/Group 8.png")).convert_alpha()
    btn_pressed = pygame.image.load(os.path.join(DATA_PATH, "rsc/Group 7.png")).convert_alpha()
    asobikata = pygame.image.load(os.path.join(DATA_PATH, "rsc/asobikata3.png")).convert_alpha()
    body = pygame.image.load(os.path.join(DATA_PATH, "rsc/body1.png")).convert_alpha()
    body_left = pygame.image.load(os.path.join(DATA_PATH, "rsc/body_left.png")).convert_alpha()
    body_right = pygame.image.load(os.path.join(DATA_PATH, "rsc/body_right.png")).convert_alpha()
    body_leg_left = pygame.image.load(os.path.join(DATA_PATH, "rsc/body_leg_left.png")).convert_alpha()
    body_leg_right = pygame.image.load(os.path.join(DATA_PATH, "rsc/body_leg_right.png")).convert_alpha()
    logo = pygame.image.load(os.path.join(DATA_PATH, "rsc/logo.png")).convert_alpha()
    title_botton = pygame.image.load(os.path.join(DATA_PATH, "rsc/title_botton.png")).convert_alpha()
    replay_botton = pygame.image.load(os.path.join(DATA_PATH, "rsc/replay_botton.png")).convert_alpha()
except Exception as e:
    print(f"エラー: 画像リソースの読み込みに失敗しました。 {e}")
    print("rscフォルダが実行ファイルと同じ階層にあるか確認してください。")

# === 画像サイズ変更・位置指定 ===
# (変更なし...省略)
def scale_image(img, scale):
    w, h = img.get_size()
    return pygame.transform.scale(img, (int(w * scale), int(h * scale)))
btn_rect = btn_normal.get_rect(center=(340, 500))
btn_rect2 = btn_normal.get_rect(center=(340, 505))
hand_left_img_mini = scale_image(hand_left_img, 0.3)
hand_left_2_img_mini = scale_image(hand_left_2_img, 0.3)
hand_right_img_mini = scale_image(hand_right_img, 0.3)
hand_right_2_img_mini = scale_image(hand_right_2_img, 0.3)
leg_left_img_mini = scale_image(leg_left_img, 0.3)
leg_left_2_img_mini = scale_image(leg_left_2_img, 0.3)
leg_right_img_mini = scale_image(leg_right_img, 0.3)
leg_right_2_img_mini = scale_image(leg_right_2_img, 0.3)
logo_mini = scale_image(logo, 0.6)
title_botton_mini = scale_image(title_botton, 0.35)
replay_botton_mini = scale_image(replay_botton, 0.35)
hand_left_rect = hand_left_img_mini.get_rect(center=(WIDTH // 2 - 180, HEIGHT // 2 + 240))
hand_left_2_rect = hand_left_2_img_mini.get_rect(center=(WIDTH // 2 - 180, HEIGHT // 2 + 240))
hand_right_rect = hand_right_img_mini.get_rect(center=(WIDTH // 2 + 180, HEIGHT // 2 + 240))
hand_right_2_rect = hand_right_2_img_mini.get_rect(center=(WIDTH // 2 + 180, HEIGHT // 2 + 240))
leg_left_rect = leg_left_img_mini.get_rect(center=(WIDTH // 2 - 60, HEIGHT // 2 + 240))
leg_left_2_rect = leg_left_2_img_mini.get_rect(center=(WIDTH // 2 - 60, HEIGHT // 2 + 240))
leg_right_rect = leg_right_img_mini.get_rect(center=(WIDTH // 2 + 60, HEIGHT // 2 + 240))
leg_right_2_rect = leg_right_2_img_mini.get_rect(center=(WIDTH // 2 + 60, HEIGHT // 2 + 240))
body_mini = scale_image(body, 0.6)
body_left_mini = scale_image(body_left, 0.6)
body_right_mini = scale_image(body_right, 0.6)
body_leg_left_mini = scale_image(body_leg_left, 0.6)
body_leg_right_mini = scale_image(body_leg_right, 0.6)
body_rect = body_left_mini.get_rect(center=(WIDTH // 2 + 380, HEIGHT // 2 - 150))
logo_rect = logo_mini.get_rect(center=(WIDTH // 2 - 250, HEIGHT // 2))
title_botton_rect = logo_mini.get_rect(center=(WIDTH // 2 + 220, HEIGHT // 2 + 150))
replay_botton_rect = logo_mini.get_rect(center=(WIDTH // 2 - 70, HEIGHT // 2 + 150))

try:
    background = pygame.image.load(os.path.join(DATA_PATH, "rsc/title_back.png")).convert_alpha()
    background = pygame.transform.scale(background, (WIDTH, HEIGHT))
except:
    background = None

# === 定数, スコア, 判定エフェクト, ノーツ描画 ===
# (変更なし...省略)
LANE_COUNT = 4
LANE_WIDTH_BOTTOM = 125
LANE_WIDTH_TOP = 75
LANE_HEIGHT = HEIGHT
NOTE_SPEED = 2
HIT_LINE_Y = HEIGHT - 200
HIT_RANGE = 25
LANE_KEYS = [pygame.K_d, pygame.K_f, pygame.K_j, pygame.K_k]
score = 0
combo = 0
max_combo = 0
font = pygame.font.SysFont("arial", 28)
combo_font = pygame.font.SysFont("arial", 40, bold=True)
small_font = pygame.font.SysFont("arial", 22, bold=True)
class JudgeEffect:
    base_font = pygame.font.SysFont("arial", 60, bold=True)
    cache = {
        "PERFECT": base_font.render("PERFECT", True, (255, 255, 120)),
        "GOOD": base_font.render("GOOD", True, (100, 200, 255)),
        "MISS": base_font.render("MISS", True, (255, 100, 100))
    }
    def __init__(self, text):
        self.text = text
        self.surface = JudgeEffect.cache[text]
        self.timer = 0
        self.duration = 45
    def draw(self, surface):
        progress = self.timer / self.duration
        scale = 1.0 + 0.2 * (0.5 - abs(progress - 0.5)) * 2
        alpha = 255 if progress < 0.6 else int(255 * (1 - (progress - 0.6) / 0.4))
        scaled = pygame.transform.rotozoom(self.surface, 0, scale)
        scaled.set_alpha(alpha)
        rect = scaled.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        surface.blit(scaled, rect)
        self.timer += 1
        return self.timer < self.duration
judge_effects = []
def interpolate(y_ratio, top_val, bottom_val):
    return top_val + (bottom_val - top_val) * y_ratio
def draw_glow_circle(surface, color, pos, radius):
    glow = pygame.Surface((radius * 2, radius * 2), pygame.SRCALPHA)
    pygame.draw.circle(glow, (*color, 40), (radius, radius), radius)
    surface.blit(glow, (pos[0] - radius, pos[1] - radius), special_flags=pygame.BLEND_RGBA_ADD)
    pygame.draw.circle(surface, color, pos, radius)

# === ノーツクラス (Note, RapidNote) ===
# (変更なし...省略)
class Note:
    def __init__(self, lane):
        self.lane = lane
        self.y = 0
        self.hit = False
        self.judged = False
    def update(self):
        self.y += NOTE_SPEED
    def draw(self):
        y_ratio = self.y / LANE_HEIGHT
        lane_center_bottom = WIDTH / 2 + (self.lane - LANE_COUNT / 2 + 0.5) * LANE_WIDTH_BOTTOM
        lane_center_top = WIDTH / 2 + (self.lane - LANE_COUNT / 2 + 0.5) * LANE_WIDTH_TOP
        x = interpolate(y_ratio, lane_center_top, lane_center_bottom)
        size = interpolate(y_ratio, 10, 35)
        color = (255, 255, 255) if not self.hit else (255, 255, 120)
        draw_glow_circle(screen, color, (int(x), int(y_ratio * LANE_HEIGHT)), int(size))
class RapidNote(Note):
    def __init__(self, lane, hit_goal=None):
        super().__init__(lane)
        self.hit_goal = hit_goal if hit_goal is not None else random.randint(8, 14)
        self.hits_done = 0
        self.active = False
        self.finished = False
        self.lock_time = 90
    def update(self):
        if not self.active:
            self.y += NOTE_SPEED
        elif self.finished:
            self.judged = True
    def draw(self):
        y_ratio = self.y / LANE_HEIGHT
        lane_center_bottom = WIDTH / 2 + (self.lane - LANE_COUNT / 2 + 0.5) * LANE_WIDTH_BOTTOM
        lane_center_top = WIDTH / 2 + (self.lane - LANE_COUNT / 2 + 0.5) * LANE_WIDTH_TOP
        x = interpolate(y_ratio, lane_center_top, lane_center_bottom)
        size = interpolate(y_ratio, 15, 45)
        color = (52, 207, 210) if not self.active else (255, 180, 100)
        draw_glow_circle(screen, color, (int(x), int(y_ratio * LANE_HEIGHT)), int(size))
        if self.active and not self.finished:
            remain = max(0, self.hit_goal - self.hits_done)
            txt = small_font.render(f"x{remain}", True, (255, 255, 255))
            rect = txt.get_rect(center=(int(x), int(y_ratio * LANE_HEIGHT) - 30))
            screen.blit(txt, rect)

# === 譜面読み込み ===
# (変更なし...省略)
def load_chart(path):
    try:
        with open(path, "r", encoding="utf-8") as f:
            return json.load(f)
    except Exception as e:
        print("Failed to load chart:", e)
        return []

# === ゲーム本編 ===
def game_loop(chart_path="chart_easy.json", gesture_queue=None): #
    global score, combo, max_combo
    NOTES = []
    score = combo = max_combo = 0
    judge_effects.clear()
    running = True

    chart = load_chart(os.path.join(DATA_PATH, chart_path)) 
    chart_index = 0
    start_time = pygame.time.get_ticks()
    lane_locked = {i: 0 for i in range(LANE_COUNT)}

    # BGM再生
    if os.path.exists(START_BGM):
        try:
            pygame.mixer.music.load(START_BGM)
            pygame.mixer.music.play()
        except Exception as e:
            print("Warning: failed to play BGM:", e)

    # === ★ 修正: チカチカ防止用のラッチタイマー ===
    latch_ms = 200

    left_hand_latch_timer = 0
    right_hand_latch_timer = 0
    # ジェスチャーが途切れてもこのミリ秒間は「押しっぱなし」として扱う
    GESTURE_LATCH_MS = latch_ms
    
    # === 足ラッチ（チカチカ防止） ===
    leg_left_latch_timer = 0
    leg_right_latch_timer = 0
    LEG_LATCH_MS = latch_ms   

    # ジェスチャー名の定義
    GESTURE_GOO = 'Closed_Fist'
    # === ★ 修正ここまで ===

    # whileループの外側に変数を用意
    notes_cleared_time = None  # ノーツが全部消えた時間
    WAIT_AFTER_NOTES_MS = 2000  # 2000ms = 2秒待つ

    while running:
        now = pygame.time.get_ticks() - start_time  # 経過時間（ms）

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                
        # === 変更点 1: ジェスチャー入力の処理 ===
        current_gestures = {'Left': 'None', 'Right': 'None'}
        if gesture_queue:
            try:
                while not gesture_queue.empty():
                    current_gestures = gesture_queue.get_nowait()
            except Exception:
                pass 
    
        # 左手(グー)が検出されたら、タイマーを「現在時刻 + 150ms」にセット
        if current_gestures.get('Right') == GESTURE_GOO:
            left_hand_latch_timer = now + GESTURE_LATCH_MS
        
        # 右手(Pointing_Up)が検出されたら、タイマーをセット
        if current_gestures.get('Left') == GESTURE_GOO:
            right_hand_latch_timer = now + GESTURE_LATCH_MS
        
        # === ★ 修正: ラッチされた状態かどうかを判断 ===
        is_left_goo_active = (now < left_hand_latch_timer)
        is_right_goo_active = (now < right_hand_latch_timer)
        
        # === 変更点 2: ジェスチャーを仮想キーにマッピング ===
        # (ラッチされた状態 'is_..._active' を使うように変更)
        gesture_keys = {
            pygame.K_d: is_left_goo_active,
            pygame.K_f: False,
            pygame.K_j: False,                                          
            pygame.K_k: is_right_goo_active
        }
        
        # === 変更点 3: キーボード入力を別途取得 ===
        kb_keys = pygame.key.get_pressed()
        
        
        # === 背景・UI描画 ===
        # (変更なし...省略)
        if background:
            screen.fill((255, 248, 240))
        else:
            screen.fill((10, 10, 30))
        for i in range(LANE_COUNT):
            if lane_locked[i] > 0:
                lane_locked[i] -= 1
        while chart_index < len(chart) and now >= chart[chart_index]["time"]:
            d = chart[chart_index]
            lane = int(d.get("lane", 0)) % LANE_COUNT
            if lane_locked.get(lane, 0) == 0:
                t = d.get("type", "normal")
                if t == "rapid":
                    n = RapidNote(lane, hit_goal=d.get("hit_goal"))
                    NOTES.append(n)
                else:
                    NOTES.append(Note(lane))
            chart_index += 1
        for i in range(LANE_COUNT):
            lane_x_bottom = WIDTH / 2 + (i - LANE_COUNT / 2) * LANE_WIDTH_BOTTOM
            lane_x_top = WIDTH / 2 + (i - LANE_COUNT / 2) * LANE_WIDTH_TOP
            pygame.draw.polygon(screen, (106, 69, 35),
                                [(lane_x_top, 0), (lane_x_top + LANE_WIDTH_TOP, 0),
                                 (lane_x_bottom + LANE_WIDTH_BOTTOM, LANE_HEIGHT),
                                 (lane_x_bottom, LANE_HEIGHT)])
            pygame.draw.line(screen, (255, 255, 255),
                             (lane_x_bottom, LANE_HEIGHT),
                             (lane_x_top, 0), 3)
        pygame.draw.line(screen, (255, 255, 255), (0, HIT_LINE_Y), (WIDTH, HIT_LINE_Y), 3)

        
        # === IMUデータの読み取り ===
        imu_right_data = imu_right.read_sensor_data()  # COM3（右足）
        imu_left_data  = imu_left.read_sensor_data()   # COM4（左足）

        # デフォルト状態
        leg_left_active = False
        leg_right_active = False

        # --- 左足（COM4） ---
        if imu_left_data is not None:
            if isinstance(imu_left_data, str):
                if imu_left_data == "2":     # 左足 IMU が送信する値
                    leg_left_active = True
            elif isinstance(imu_left_data, dict):
                leg_left_active = imu_left_data.get("leg_left", 0) == 1

        # --- 右足（COM3） ---
        if imu_right_data is not None:
            if isinstance(imu_right_data, str):
                if imu_right_data == "1":     # 右足 IMU が送信する値
                    leg_right_active = True
            elif isinstance(imu_right_data, dict):
                leg_right_active = imu_right_data.get("leg_right", 0) == 1

        # 現在の時刻
        imu_now = pygame.time.get_ticks()

        # ラッチ処理
        if leg_left_active:
            leg_left_latch_timer = imu_now + LEG_LATCH_MS
        if leg_right_active:
            leg_right_latch_timer = imu_now + LEG_LATCH_MS

        # ラッチ状態を反映
        leg_left_active = imu_now < leg_left_latch_timer
        leg_right_active = imu_now < leg_right_latch_timer

        # ノーツ判定に反映
        gesture_keys[pygame.K_f] = gesture_keys.get(pygame.K_f, False) or leg_left_active
        gesture_keys[pygame.K_j] = gesture_keys.get(pygame.K_j, False) or leg_right_active


        # === UI描画 ===
        # 左手（Mediapipe + キーボード）
        if kb_keys[pygame.K_d] or gesture_keys[pygame.K_d]:
            screen.blit(hand_left_2_img_mini, hand_left_2_rect)
            screen.blit(body_left_mini, body_rect)
        else:
            screen.blit(hand_left_img_mini, hand_left_rect)
            screen.blit(body_mini, body_rect)

        # 右手（Mediapipe + キーボード）
        if kb_keys[pygame.K_k] or gesture_keys[pygame.K_k]:
            screen.blit(hand_right_2_img_mini, hand_right_2_rect)
            screen.blit(body_right_mini, body_rect)
        else:
            screen.blit(hand_right_img_mini, hand_right_rect)
            screen.blit(body_mini, body_rect)

        # 左足（IMU）
        if leg_left_active:
            screen.blit(leg_left_2_img_mini, leg_left_2_rect)
            screen.blit(body_leg_left_mini, body_rect)
        else:
            screen.blit(leg_left_img_mini, leg_left_rect)
            screen.blit(body_mini, body_rect)

        # 右足（IMU）
        if leg_right_active:
            screen.blit(leg_right_2_img_mini, leg_right_2_rect)
            screen.blit(body_leg_right_mini, body_rect)
        else:
            screen.blit(leg_right_img_mini, leg_right_rect)
            screen.blit(body_mini, body_rect)

        for note in NOTES[:]:  # コピーでループ
            note.update()
            note.draw()
            
            # 連打ノーツの処理
            if isinstance(note, RapidNote):
                if note.judged or (note.y > LANE_HEIGHT):  # 終了条件 or 画面外
                    try:
                        NOTES.remove(note)
                    except ValueError:
                        pass
                continue  # 通常ノーツ処理は飛ばす
            
            # 通常ノーツ処理
            if note.y > LANE_HEIGHT and not note.judged:
                note.judged = True
                combo = 0
                judge_effects.append(JudgeEffect("MISS"))
                try:
                    NOTES.remove(note)
                except ValueError:
                    pass

        # === 変更点 5: ノーツ入力判定 (変更なし) ===
        for i, key in enumerate(LANE_KEYS):
            if kb_keys[key] or gesture_keys[key]:
                for note in NOTES:
                    if note.lane == i and not note.judged:
                        if isinstance(note, RapidNote):
                            if not note.active and abs(note.y - HIT_LINE_Y) < HIT_RANGE:
                                note.active = True
                                note.y = HIT_LINE_Y
                                combo += 1
                                score += 300
                                max_combo = max(max_combo, combo)
                                judge_effects.append(JudgeEffect("PERFECT"))
                                lane_locked[note.lane] = note.lock_time
                            elif note.active and not note.finished:
                                note.hits_done += 1
                                combo += 1
                                score += 50
                                max_combo = max(max_combo, combo)
                                if note.hits_done >= note.hit_goal:
                                    note.finished = True
                                    note.judged = True
                                    judge_effects.append(JudgeEffect("PERFECT"))
                            break
                        else:
                            diff = abs(note.y - HIT_LINE_Y)
                            if diff < 10:
                                note.hit = True
                                note.judged = True
                                score += 300
                                combo += 1
                                max_combo = max(max_combo, combo)
                                judge_effects.append(JudgeEffect("PERFECT"))
                                try:
                                    NOTES.remove(note)
                                except ValueError:
                                    pass
                                break
                            elif diff < 25:
                                note.hit = True
                                note.judged = True
                                score += 100
                                combo += 1
                                max_combo = max(max_combo, combo)
                                judge_effects.append(JudgeEffect("GOOD"))
                                try:
                                    NOTES.remove(note)
                                except ValueError:
                                    pass
                                break

        # === スコア・FPS・判定描画 ===
        # (変更なし...省略)
        screen.blit(font.render(f"SCORE: {score}", True, (255, 255, 255)), (30, 30))
        if combo > 0:
            combo_text = combo_font.render(f"COMBO: {combo}", True, (255, 255, 180))
            screen.blit(combo_text, combo_text.get_rect(center=(WIDTH // 2, 80)))
        fps = int(clock.get_fps())
        screen.blit(font.render(f"FPS: {fps}", True, (180, 180, 255)), (WIDTH - 120, 30))
        for effect in judge_effects[:]:
            if not effect.draw(screen):
                judge_effects.remove(effect)

        if chart_index >= len(chart) and len(NOTES) == 0:
            if notes_cleared_time is None:
                # ノーツ終了を検知した時刻を保存
                notes_cleared_time = now
            elif now - notes_cleared_time >= WAIT_AFTER_NOTES_MS:
                # 待機時間が経過したら結果画面へ
                print("[INFO] All notes finished. Moving to result screen.")
                running = False
                break
        else:
            # ノーツが残っている場合はリセット
            notes_cleared_time = None

        pygame.display.flip()
        clock.tick(60)
    # === while ループ終了後 ===
    print("1")
    pygame.mixer.music.stop()
    result_screen(score, max_combo)



# === スタート画面 ===
def start_screen(gesture_queue=None): #
    # (変更なし...省略)
    if os.path.exists(START_BGM):
        try:
            pygame.mixer.music.load(START_BGM)
            pygame.mixer.music.play(-1)
        except Exception as e:
            print("Warning: failed to play title BGM:", e)

    title_font = pygame.font.SysFont("arial", 80, bold=True)
    sub_font = pygame.font.SysFont("arial", 30)
    blink = 0
    
    try:
        font_path = os.path.join(DATA_PATH, "rsc/NotoSansJP-Medium.ttf")
        title_font_jp = pygame.font.Font(font_path, 25)
        title_font2_jp = pygame.font.Font(font_path, 35)
    except Exception as e:
        print(f"Warning: 日本語フォントのロードに失敗 {e}")
        # フォールバックとしてデフォルトフォントを使う
        title_font_jp = pygame.font.SysFont("arial", 25)
        title_font2_jp = pygame.font.SysFont("arial", 35)


    while True:
        if background:
            screen.blit(background, (0, 0))
        else:
            screen.fill((10, 10, 30))

        try:
            orig_w, orig_h = gigibaba_img.get_size()
            scale = 0.25
            gigibaba_scaled = pygame.transform.smoothscale(gigibaba_img, (int(orig_w * scale), int(orig_h * scale)))
            screen.blit(gigibaba_scaled, (WIDTH/2+10, HEIGHT/2-80))
        except NameError:
             pass 

        try:
            title = title_font_jp.render("座ったままで、楽しく運動", True, (100, 28, 0))
            rect = title.get_rect(center=(WIDTH // 2-250, HEIGHT // 2 - 80))
            screen.blit(title, rect)
            screen.blit(logo_mini, logo_rect)
        except Exception:
             pass 

        mouse_pos = pygame.mouse.get_pos()
        mouse_pressed = pygame.mouse.get_pressed()[0] 

        try:
            btn_normal_min = scale_image(btn_normal, 0.35)
            btn_pressed_min = scale_image(btn_pressed, 0.35)
            btn_rect_min = btn_normal_min.get_rect(center=btn_rect.center) 
            btn_rect_min2 = btn_normal_min.get_rect(center=btn_rect2.center) 
            
            if btn_rect.collidepoint(mouse_pos):
                screen.blit(btn_pressed_min, btn_rect_min2)
                if mouse_pressed:
                    pygame.mixer.music.stop()
                    intro_sequence()
                    game_loop(gesture_queue=gesture_queue) 
                    break
            else:
                screen.blit(btn_normal_min, btn_rect_min)
        except NameError:
            pass 

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                return
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
                pygame.mixer.music.stop()
                intro_sequence()
                game_loop(gesture_queue=gesture_queue) 
                return

        pygame.display.flip()
        clock.tick(60)

# === リザルト画面 ===
def result_screen(score, max_combo):
    try:
        font_path = os.path.join(DATA_PATH, "rsc/NotoSansJP-Medium.ttf")
        title_font_jp = pygame.font.Font(font_path, 40)
        title_font2_jp = pygame.font.Font(font_path, 25)
    except Exception as e:
        print(f"Warning: 日本語フォントのロードに失敗 {e}")
        title_font_jp = pygame.font.SysFont("arial", 25)
        title_font2_jp = pygame.font.SysFont("arial", 35)


    running = True
    while running:
        screen.fill((255, 248, 240))
        
        # タイトル
        if score/3300 >= 0.8:
            title_surf = title_font_jp.render("素晴らしい記録です！", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)
        elif score/3300 >= 0.5:
            title_surf = title_font_jp.render("なかなかよくできました！", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)
        else:
            title_surf = title_font_jp.render("無理せず続けていきましょう!", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)

        
        # スコア
        score_surf = title_font2_jp.render(f"スコア: {score}", True, (100, 28, 0))
        score_rect = score_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(score_surf, score_rect)

        # 最大コンボ
        combo_surf = title_font2_jp.render(f"最大コンボ: {max_combo}", True, (100, 28, 0))
        combo_rect = combo_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 50))
        screen.blit(combo_surf, combo_rect)

        # ボタン描画
        screen.blit(title_botton_mini, title_botton_rect)
        screen.blit(replay_botton_mini, replay_botton_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:  # 左クリック
                if title_botton_rect.collidepoint(event.pos):
                    running = False
                    start_screen()  # タイトルへ
                elif replay_botton_rect.collidepoint(event.pos):
                    running = False
                    game_loop()  # もう一度遊ぶ

# === 開始シーケンス ===
def intro_sequence():
    # (変更なし...省略)
    try:
        screen.fill((255, 248, 240))
        asobikata_min = scale_image(asobikata, 0.6)
        rect = asobikata_min.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(asobikata_min, rect)
        pygame.display.flip()
    except NameError:
        print("Warning: 'asobikata' 画像がロードされていません。シーケンスをスキップします。")
        waiting = False
    else:
        waiting = True

    while waiting:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                waiting = False
    screen.fill((255, 248, 240))
    pygame.display.flip()
    draw_text_center("3", 1200)
    screen.fill((255, 248, 240))
    draw_text_center("2", 1000)
    screen.fill((255, 248, 240))
    draw_text_center("1", 1000)

def draw_text_center(text, delay):
    # (変更なし...省略)
    font_big = pygame.font.SysFont("arial", 80, bold=True)
    surface = font_big.render(text, True, (100, 28, 0))
    rect = surface.get_rect(center=(WIDTH // 2, HEIGHT // 2))
    screen.blit(surface, rect)
    pygame.display.flip()
    pygame.time.delay(delay)

# (if __name__ == "__main__": ブロックは main.py にあるため削除)

# === リザルト画面 ===
def result_screen(score, max_combo):
    try:
        font_path = os.path.join(DATA_PATH, "rsc/NotoSansJP-Medium.ttf")
        title_font_jp = pygame.font.Font(font_path, 40)
        title_font2_jp = pygame.font.Font(font_path, 25)
    except Exception as e:
        print(f"Warning: 日本語フォントのロードに失敗 {e}")
        title_font_jp = pygame.font.SysFont("arial", 25)
        title_font2_jp = pygame.font.SysFont("arial", 35)


    running = True
    while running:
        screen.fill((255, 248, 240))
        
        # タイトル
        if score/3300 >= 0.8:
            title_surf = title_font_jp.render("素晴らしい記録です！", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)
        elif score/3300 >= 0.5:
            title_surf = title_font_jp.render("なかなかよくできました！", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)
        else:
            title_surf = title_font_jp.render("無理せず続けていきましょう!", True, (255, 142, 24))
            title_rect = title_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 - 100))
            screen.blit(title_surf, title_rect)

        
        # スコア
        score_surf = title_font2_jp.render(f"スコア: {score}", True, (100, 28, 0))
        score_rect = score_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(score_surf, score_rect)

        # 最大コンボ
        combo_surf = title_font2_jp.render(f"最大コンボ: {max_combo}", True, (100, 28, 0))
        combo_rect = combo_surf.get_rect(center=(WIDTH // 2, HEIGHT // 2 + 50))
        screen.blit(combo_surf, combo_rect)

        # ボタン描画
        screen.blit(title_botton_mini, title_botton_rect)
        screen.blit(replay_botton_mini, replay_botton_rect)

        pygame.display.flip()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:  # 左クリック
                if title_botton_rect.collidepoint(event.pos):
                    running = False
                    gesture_process = multiprocessing.Process(
                        target=gesture_worker,
                        args=(gesture_queue,)
                    )
                    gesture_process.start()
                    start_screen()  # タイトルへ
                elif replay_botton_rect.collidepoint(event.pos):
                    running = False
                    gesture_process = multiprocessing.Process(
                        target=gesture_worker,
                        args=(gesture_queue,)
                    )
                    gesture_process.start()

                    game_loop()  # もう一度遊ぶ
