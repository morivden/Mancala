#include <stdio.h>
#include <stdlib.h>
#define NUM 14
#define STONE 3
#define SIZE 256

int brd[NUM];

void SetBoard(void) {
  int i;

  for (i = 0; i < NUM; i++) {
    brd[i] = STONE;
  }

  brd[0] = 0, brd[NUM / 2] = 0;

  return;
}

void ShowBoard(void) {
  int i;

  printf("%d ", brd[0]);

  for (i = 1; i < NUM / 2; i++) {
    printf("%d ", brd[i]);
  }

  printf("%d\n", brd[NUM / 2]);
  printf("%d ", brd[0]);

  for (i = NUM - 1; i > NUM / 2; i--) {
    printf("%d ", brd[i]);
  }

  printf("%d\n", brd[NUM / 2]);


  return;
}

int WinLose(void) {
  int s1 = 0;
  int s2 = 0;
  int i;

  for (i = 1; i < NUM / 2; i++) {
    s1 += brd[i];
  }

  for (i = NUM / 2 + 1; i < NUM; i++) {
    s2 += brd[i];
  }

  if (s1 == 0) {
    puts("player1 Win!");
        
    return 1;
  }  else if (s2 == 0) {
    puts("player2 Win!");
        
    return -1;
  } else {
    return 0;
  }
}

int Hand(int turn) {
  char n[SIZE];
  int p;
  
  if ( turn == 1 ) {
    do {

      printf("Player1 : ");
      scanf("%s", n);
      p = atoi(n);

    } while (p <= 0 || p >= NUM / 2);    
  } else {
    do {

      printf("Player2 : ");
      scanf("%s", n);
      p = atoi(n);

    } while (p <= NUM / 2 || p >= NUM );    
  }

  return p;
}

int Sowing(int turn) {
  int i;
  int p;
  int temp;
  int end;

  p = Hand(turn);

  printf("%d\n", p);

  // 変数に値を入れる
  temp = brd[p];
  end = p + temp;

  // 指定した場所の初期化
  brd[p] = 0;
    
  // 種まきをする
  for (i = 1; i <= temp; i++) {
    if (p + i >= NUM) {
      brd[p + i - NUM]++;
    }  else {
      brd[p + i]++;
    }
  }

  if (end == NUM || end == NUM / 2) {
    if (WinLose() != 0) {
      return turn;
    } else {
    ShowBoard();
    Sowing(turn);
    }
  }

  // ターンの変更
  turn *= -1;

  return turn;
}

int main(void)
{
  int turn = 1;
  SetBoard();

  do {        
    turn = Sowing(turn);
    ShowBoard();
  } while (WinLose() == 0);
    
  return 0;
}
