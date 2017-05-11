#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<string.h>

bool  LED_board[11] = {};//LEDボードの状態を示す
bool  TOUCH_board[11] = {};//新たにタッチされたボードを示す


void output(bool *led){//LEDボードをターミナルに出力する
  for(int i=0; i<9; i++){
    if(led[i]==true){
      printf("■ ");
    }
    else if(led[i]==false){
      printf("□ ");
    }
    if(i%3==2){
      printf("\n");
    }
  }
}

bool is_touched(int x) {// 一つ前の周期から現在に至るまでにそれぞれのタッチセンサがタッチされたかどうか
  if(TOUCH_board[x]){
    return true;
  }else{
    return false;
  }
}


bool is_any_sensor_touched() {//  一つ前の周期から現在に至るまでにタッチされたセンサの位置(一つのみと仮定)
  for (int i = 0;i<11;i++){
    if(is_touched(i)){
      return true;
    }
  }
  return false;
}


int get_touch_pos() {//タッチされたパネルを返す
  for(int i=0;i<11;i++){
    if(is_touched(i)){
      return i;
    }
  }
  printf("ERROR1\n");
  return 100;
}

void turn_panel(int pos){//パネルを反転させる
  LED_board[pos] = !LED_board[pos];
}

void feedback_on_LED_panel(int touched_pos){//それぞれのパネルに触れたときの反応
  if(touched_pos==0){
    turn_panel(0);
    turn_panel(1);
    turn_panel(3);
  }else if(touched_pos==1){
    turn_panel(0);
    turn_panel(1);
    turn_panel(2);
    turn_panel(4);
  }else if(touched_pos==2){
    turn_panel(1);
    turn_panel(2);
    turn_panel(5);
  }else if(touched_pos==3){
    turn_panel(0);
    turn_panel(3);
    turn_panel(4);
    turn_panel(6);
  }else if(touched_pos==4){
    turn_panel(1);
    turn_panel(3);
    turn_panel(4);
    turn_panel(5);
    turn_panel(7);
  }else if(touched_pos==5){
    turn_panel(2);
    turn_panel(4);
    turn_panel(5);
    turn_panel(8);
  }else if(touched_pos==6){
    turn_panel(3);
    turn_panel(6);
    turn_panel(7);
  }else if(touched_pos==7){
    turn_panel(4);
    turn_panel(6);
    turn_panel(7);
    turn_panel(8);
  }else if(touched_pos==8){
    turn_panel(5);
    turn_panel(7);
    turn_panel(8);
  }else{
    printf("ERROR3\n");
  }
}

bool is_game_clear() {//ゲームクリアしているか否かを返す
  for(int i=0;i<9;i++){
    if(LED_board[i]){
      return false;
    }
  }
  return true;
}

void callback(){//
    int touched_pos = get_touch_pos();
    feedback_on_LED_panel(touched_pos);

    if (is_game_clear()) {
      output(LED_board);
       printf("\n*****CLEAR*****\n");
    }
}

void loop() {//ボードがタッチされたらLoopに入る
  if (is_any_sensor_touched()){
      callback();
  }
}

void touch(int n){//TOUCHボードに入力を反映する。
  TOUCH_board[n]=true;
}

void reset(){//リセット
  srand((unsigned)time(NULL));
  for(int i=0;i<11;i++){
    LED_board[i]=rand()%2;
  }
  memset(TOUCH_board, false, sizeof(TOUCH_board));
  printf("LIGHTS OFF\n");
  printf("START!!\n");
}


int main(int argc, char const *argv[]) {
  int position;
  reset();
  while(!is_game_clear()){
    for(int i =0;i<11;i++){
        TOUCH_board[i]=false;
    }
    output(LED_board);
    printf("type 1~9 (10:reset) \n");
    scanf("%d",&position);
    if(position==10){
      reset();
    }else if(position>=1 && position<=9){
      touch(position-1);
    }
    loop();
  }

  return 0;
}
