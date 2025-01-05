#include "board.h"
#include "levels.h"
#include "sweeper.h"
#include <stdio.h>
#include <stdlib.h>

Board * generatorForBoard() {

    Board * board = (Board*) malloc(sizeof(Board));
    Pos * pos = (Pos*) malloc(sizeof(Pos));

    iChooseYou(board);
    commandPicker(pos,0);
    createBoardData(board);

    int i,j,k,l;
    int r = board->r;
    int c = board->c;
    int x = pos->x;
    int y = pos->y;

    for(k=y-1;k<=y+1;k++) {
        if (k>=0 && k<c) {
            for(l=x-1;l<=x+1;l++) {
                if (l>=0 && l<r) {
                    board->data[l][k]=-2;
                }
            }
        }
    }

    board->data[x][y]=0;

    printBoard(board);

    int count = 0;
    int temp;
    i=0;
    j=0;

    while (count<board->m) {
        i=rand() % r;
        j=rand() % c;

        temp = board->data[i][j];

        if (temp != 0 && temp != -2 && temp !=-1)
            board->data[i][j]=-1;
            count++;
    }

    printBoard(board);

    count = 0;

    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            for(k=y-1;k<=y+1;k++) {
                if (k>=0 && k<c) {
                    for(l=x-1;l<=x+1;l++) {
                        if (l>=0 && l<r) {
                            if (board->data[l][k] == -1 && board->data[i][j] != -1) {
                                count++;
                            }
                        }
                    }
                }
            }
            board->data[i][j]=count;
            count=0;
        }
    }

    printBoard(board);
}

Board * createBoardData(Board *board) {
    int i,j;
    int r = board->r;
    int c = board->c;

    board->data = (int**) malloc(sizeof(int*) * r);
    for (i=0; i < r; i++) {
        board->data[i] = (int*) malloc(sizeof(int)*c);
    }
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            board->data[i][j]=-3;
        }
    }
}

void printBoard(Board *board) {
    int i,j;
    int r = board->r;
    int c = board->c;
    for (j = 0; j < c; j++) {
        printf("=====");
    }
    printf("=\n");
    for (i=0;i<r;i++) {
        printf("|");
        for (j = 0; j < c; j++) {
            if (board->data[i][j] >= 0)
                printf("  %d |", board->data[i][j]);
            else 
                printf(" %d |", board->data[i][j]);       
        }
        printf("\n");
    }
    for (j = 0; j < c; j++) {
        printf("=====");
    }
    printf("=\n");
    printf("\n");
}



