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

int Hand(int turn) {
    int p;
    char n[SIZE];

    do {
        printf("input position : ");
        scanf("%s", &n);
        p = atoi(n);
    } while (p <= 0 || p >= NUM || p == NUM / 2);

    printf("%d\n", p);
    
    return p;
}

int Sowing(int p) {
    int i;
    int temp = brd[p];
    int end = p + temp;
    brd[p] = 0;

    for (i = 1; i <= temp; i++) {
        if (p + i >= NUM) {
            brd[p + i - NUM]++;
        }  else {
            brd[p + i]++;
        }
    }

    if (end == NUM || end == NUM / 2) {
        return -1;
    }
    
    return 1;
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

int main(void)
{
    int p;
    
    SetBoard();

    do {        
        p = Hand();

        while ()
        Sowing(p);

        ShowBoard();
        
    } while (WinLose() == 0);
    
    return 0;
}
