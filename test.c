#include<stdio.h>
#include <stdbool.h>

int main(int argc, char const *argv[]) {
  bool  LED_board[3][3] = {};
  LED_board[1][1] = true;
  printf("%d\n",LED_board[1][1]);
  printf("%d\n",LED_board[0][0]);
  return 0;
}
