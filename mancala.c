#include <stdio.h>
#include <stdlib.h>

#define NUM 14
#define STONE 3
#define SIZE 256

// ボードの宣言
int brd[NUM] = {0, 3, 3, 3, 3, 3, 3,
                0, 3, 3, 3, 3, 3, 3};

//==== ボートの初期設定関数
int SetBoard(void) {
    int i;
    int s1 = 0;
    int s2 = 0;
    int flag = 0;

    for (i = 1; i < NUM / 2; i++) {
        if (brd[i] < 0) {
            flag = -1;
            break;
        }
        s1 += brd[i];
    }

    for (i = NUM / 2 + 1; i < NUM; i++) {
        if (brd[i] < 0) {
            flag = -1;
            break;
        }
        s2 += brd[i];
    }

    if (s1 > 0 && s2 > 0 && flag == 0) {
        return 1;
    }
    
    return 0;
}

//==== ボードの出力関数
void ShowBoard(void) {
    int i;

    printf("%d ", brd[0]);

    // プレイヤ1のボード表示
    for (i = 1; i < NUM / 2; i++) {
        printf("%d ", brd[i]);
    }

    // 大きい穴の表示
    printf("%d\n", brd[NUM / 2]);
    printf("%d ", brd[0]);

    // プレイヤ2の表示
    for (i = NUM - 1; i > NUM / 2; i--) {
        printf("%d ", brd[i]);
    }

    // 大きい穴の表示
    printf("%d\n\n", brd[NUM / 2]);

    return;
}

//==== 勝敗の判定関数
int WinLose(void) {
    int s1 = 0;
    int s2 = 0;
    int i;

    //== 各プレイヤの石の総計
    // プレイヤ1
    for (i = 1; i < NUM / 2; i++) {
        s1 += brd[i];
    }

    // プレイヤ2
    for (i = NUM / 2 + 1; i < NUM; i++) {
        s2 += brd[i];
    }

    // 勝敗の判定と結果出力
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

// 打ち手の入力関数
int Hand(int turn) {
    char n[SIZE];
    int p;
    int player;
    
    if (turn == 1) {
        player = 1;
    } else {
        player = 2;
    }
    
    while (1) {
        printf("Player%d: ", player);
        scanf("%s", n);
        p = atoi(n);

        if (p >= 1 && p < NUM / 2) {
            if (turn == -1) {
                p += NUM / 2;
            }
            if (brd[p] > 0) {
                break;
            }
        }
    } 
    
    return p;
}

//==== 種まきをする関数
int Sowing(int turn) {
    int i;
    int p;
    int temp;
    int end;

    // 関数Handから位置を受け取る
    p = Hand(turn);

    puts("");

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

    // ターンの終了判定
    if (end == NUM || end == NUM / 2) {
        if (WinLose() != 0) {
            return turn;
        } else {
            // 大きい穴に入れば再帰的にSowing関数を呼び出す
            ShowBoard();
            Sowing(turn);
        }
    }

    // ターンの変更
    turn *= -1;

    return turn;
}

//==== ゲーム本体
int main(void)
{
    // 変数宣言
    int turn = 1;    // ターンの初期設定

    if (SetBoard()) {
        
        ShowBoard();
        
        do {        
            turn = Sowing(turn);
            ShowBoard();
        } while (WinLose() == 0);    // 勝敗の判定
    } else {
        puts("Error!! : This game cannot start!!");
    }
    
    return 0;
}
