#include "types.h"

/*
 * TouchStateの定義はtypes.hを参照
 * 3x3のタッチパネルの状態をもつ二次元配列
 */
TouchState touch_panel[3][3];
/*
 * 3x3のLEDパネルの状態をもつ二次元配列
 * true => LED_ON, false => LED_OFF
 */
bool led_panel[3][3] = {};

/*
 *  タッチセンサの受信側のピンの始めの番号
 *  練習用はタッチセンサは7つのみ
  */
const int START_TOUCH_PIN = 2;
const int START_LED_PIN = 22;

/*
 * ゲームの初期化用関数。主にパネルの状態をもつ配列の初期化を行う。
 */
/*void init_game() {
  // 配列の初期化。
  // memsetを使うとfor文を使わずに配列の中身全てを初期化できる。
  memset(touch_panel, TouchState::None, sizeof(touch_panel) / sizeof(touch_panel[0][0]));
  memset(led_panel, false, sizeof(led_panel));
  randomSeed(analogRead(0));
  for(int x=0;x<3;x++){
    for(int y=0;y<3;y++){
      led_panel[x][y]=int(random(2));
    }
  }
}*/
void shuffle(int ary[],int size){
  randomSeed(analogRead(0));
  for(int i=0;i<size;i++){
    int j = random(9);
    int t = ary[i];
    ary[i] = ary[j];
    ary[j] = t;
  }
}

void level_set(int lv){
  int list[9] ={0,1,2,3,4,5,6,7,8,9};
  shuffle(list, 9);
  for(int i=0;i<lv;i++){
    led_panel[list[i]/3][list[i]%3] = true;
  }
}

void init_game(int lv) {
  // 配列の初期化。
  // memsetを使うとfor文を使わずに配列の中身全てを初期化できる。
  memset(touch_panel, TouchState::None, sizeof(touch_panel) / sizeof(touch_panel[0][0]));
  memset(led_panel, false, sizeof(led_panel));
  randomSeed(analogRead(0));
  level_set(lv);
}

/*
 * 各タッチパネルの状態を更新する。
 */
void renew_touch_panel_state() {
  for (int x = 0; x < 3; ++x) {
     for (int y = 0; y < 3; ++y) {
      int value = 0;
      // 練習用のタッチパネルは7つしかないので
      if (3 * x + y < 7) {
        value = digitalRead(START_TOUCH_PIN + 3 * x + y);
      }

      if (value && touch_panel[x][y] == TouchState::None) {
          touch_panel[x][y] = TouchState::Touched;
      } else if (value && touch_panel[x][y] != TouchState::None) {
          touch_panel[x][y] = TouchState::Touching;
      } else {
          touch_panel[x][y] = TouchState::None;
      }
    }
  }
}

/*
 * いづれかのタッチパネルがタッチされたかどうか
 */
bool is_touched_any_panel()
{
   for (int x = 0; x < 3; ++x) {
     for (int y = 0; y < 3; ++y) {
      if (touch_panel[x][y] == TouchState::Touched) {//???
         return true;
      }
     }
   }
   return false;
}

/*
 * ゲームがクリアされたかどうか
 */
bool is_game_clear()
{
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      if(led_panel[x][y]){
        return false;
      }
    }
  }
  return true;
}

/*
 * タッチされた場所を返す。
 * Point2iについてはtypes.hを参照。
 */
Point2i touched_pos()
{
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      if (touch_panel[x][y] == TouchState::Touched) {
        return Point2i(x, y);
      }
    }
  }
}

/*
 * タッチされた場所を渡し、3x3のLEDパネルの状態を更新する。
 */
 void renew_led_panel(Point2i touched_pos)
 {
   int dir[5][2] = {{0,0},{0,-1},{0,1},{-1,0},{1,0}};
     for(int i=0;i<5;i++){
       int nx = touched_pos.x + dir[i][0];
       int ny = touched_pos.y + dir[i][1];
       if(nx<0||nx>2){
         continue;
       }
       if(ny<0||ny>2){
         continue;
       }
       led_panel[nx][ny]=!led_panel[nx][ny];
     }
 }

void light_on()
{
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      if (led_panel[x][y]) {
        digitalWrite(START_LED_PIN + 3 * x + y, HIGH);
      } else {
        digitalWrite(START_LED_PIN + 3 * x + y, LOW);
      }
    }
  }
}

void callback()
{
  const Point2i pos = touched_pos();
  Serial.println(pos.x);
  Serial.println(pos.y);
  renew_led_panel(pos);
  light_on();
}

/*
 * 一秒間全てのLEDパネルを点灯し、消す。
 * LEDパネルが正常に動作しているかどうかの確認。
 */
void check_led_panel()
{
    for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      digitalWrite(START_LED_PIN + 3 * x + y, HIGH);
    }
  }
  delay(1000);
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {
      digitalWrite(START_LED_PIN + 3 * x + y, LOW);
    }
  }
}

void setup() {
  Serial.begin(9600);

  // setup for PIN
  for (int x = 0; x < 3; ++x) {
    for (int y = 0; y < 3; ++y) {

      if (3 * x + y < 7) {
         pinMode(START_TOUCH_PIN + 3 * x + y, INPUT);
      }
      pinMode(START_LED_PIN + 3 * x + y, OUTPUT);
    }
  }
  delay(100);
  check_led_panel();
  init_game();
  light_on();
  Serial.println("setup end");
}

void loop() {
  // put your main code here, to run repeatedly:
  renew_touch_panel_state();
  if (is_touched_any_panel()) {
    callback();
  }
  if (is_game_clear()) {
    Serial.println("game clear");
    return;
  }
  delay(100);
}
