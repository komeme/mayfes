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
void init_game() {
  // 配列の初期化。
  // memsetを使うとfor文を使わずに配列の中身全てを初期化できる。
  memset(touch_panel, TouchState::None, sizeof(touch_panel) / sizeof(touch_panel[0][0]));
  memset(led_panel, false, sizeof(led_panel));
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
      if (touch_panel[x][y] == TouchState::Touching) {
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
  // 例). タッチされたLEDパネルのON/OFFを反転する。
  //led_panel[touched_pos.x][touched_pos.y] = !led_panel[touched_pos.x][touched_pos.y];
  if(touched_pos.x==0&&touched_pos.y==0){
    led_panel[0][0]=!led_panel[0][0];
    led_panel[0][1]=!led_panel[0][1];
    led_panel[1][0]=!led_panel[1][0];
  }
  else if(touched_pos.x==0&&touched_pos.y==1){
    led_panel[0][0]=!led_panel[0][0];
    led_panel[0][1]=!led_panel[0][1];
    led_panel[0][2]=!led_panel[0][2];
    led_panel[1][1]=!led_panel[1][1];
  }
  else if(touched_pos.x==0&&touched_pos.y==2){
    led_panel[0][1]=!led_panel[0][1];
    led_panel[0][2]=!led_panel[0][2];
    led_panel[1][2]=!led_panel[1][2];
  }
  else if(touched_pos.x==1&&touched_pos.y==0){
    led_panel[0][0]=!led_panel[0][0];
    led_panel[1][0]=!led_panel[1][0];
    led_panel[1][1]=!led_panel[1][1];
    led_panel[2][0]=!led_panel[2][0];
  }else if(touched_pos.x==1&&touched_pos.y==1){
    led_panel[0][1]=!led_panel[0][1];
    led_panel[1][0]=!led_panel[1][0];
    led_panel[1][1]=!led_panel[1][1];
    led_panel[1][2]=!led_panel[1][2];
    led_panel[2][1]=!led_panel[2][1];
  }else if(touched_pos.x==1&&touched_pos.y==2){
    led_panel[0][2]=!led_panel[0][2];
    led_panel[1][1]=!led_panel[1][1];
    led_panel[1][2]=!led_panel[1][2];
    led_panel[2][2]=!led_panel[2][2];
  }else if(touched_pos.x==2&&touched_pos.y==0){
    led_panel[1][0]=!led_panel[1][0];
    led_panel[2][0]=!led_panel[2][0];
    led_panel[2][1]=!led_panel[2][1];
  }else if(touched_pos.x==2&&touched_pos.y==1){
    led_panel[1][1]=!led_panel[1][1];
    led_panel[2][0]=!led_panel[2][1];
    led_panel[2][1]=!led_panel[2][1];
    led_panel[2][2]=!led_panel[2][2];
  }else if(touched_pos.x==2&&touched_pos.y==2){
    led_panel[1][2]=!led_panel[1][2];
    led_panel[2][1]=!led_panel[2][1];
    led_panel[2][2]=!led_panel[2][2];
  }else{
    Serial.println("ERROR");
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
