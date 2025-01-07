#include "board.h"
#include "levels.h"
#include "sweeper.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Colors(int type) {
    if (type == 0) //Zmiana koloru na domyślny
        printf("\033[0m");
    if (type == 1) //Zmiana koloru na niebieski
        printf("\033[1;34m");
    if (type == 2) //Zmiana koloru na zielony
        printf("\033[1;32m");
    if (type == 3) //Zmiana koloru na czerwony
        printf("\033[1;31m");
    if (type >= 4) //Zmiana koloru na fioletowy
        printf("\033[1;35m");
    if (type == -1) //Zmiana koloru na 
        printf("\033[1;36m");
}

Board * generatorForBoard() {

    Board * board = (Board*) malloc(sizeof(Board));
    Pos * pos = (Pos*) malloc(sizeof(Pos));

    iChooseYou(board);
    commandPicker(board,pos,0);
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

    int count = 0;
    int temp;
    unsigned int seed = time(0);
    i=0;
    j=0;

    while (count<board->m) {
        i=rand_r(&seed) % r;
        j=rand_r(&seed) % c;

        temp = board->data[i][j];

        if (temp != 0 && temp != -2 && temp !=-1)
            board->data[i][j]=-1;
            count++;
    }

    count = 0;

    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            if (board->data[i][j] != -1) {
                for(k=j-1;k<=j+1;k++) {
                    if (k>=0 && k<c) {
                        for(l=i-1;l<=i+1;l++) {
                            if (l>=0 && l<r) {
                                if (board->data[l][k] == -1) {
                                    count+=1;
                                }
                            }
                        }
                    }
                }
                board->data[i][j]=count;
                
            count=0;
            }
        }
    }
    revealTiles(board,x,y);
    printBoard(board);

    while (board->Run==0) {
        commandPicker(board, pos,1);
    }



}

Board * createBoardData(Board *board) {
    int i,j;
    int r = board->r;
    int c = board->c;
    board->Run=0;

    board->data = (int**) malloc(sizeof(int*) * r);
    board->shown = (char***) malloc(sizeof(char**) * r);
    for (i=0; i < r; i++) {
        board->data[i] = (int*) malloc(sizeof(int)*c);
        board->shown[i] = (char**) malloc(sizeof(char*)*c);
    }
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            board->data[i][j]=-3;
            board->shown[i][j]=" ";
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
            if (board->shown[i][j]!=" ") {
                if (board->data[i][j] >= 0) {
                    Colors(board->data[i][j]);
                    printf("  %s", board->shown[i][j]);
                } 
                else {
                    Colors(-1);       
                    printf(" %s", board->shown[i][j]);
                }
                Colors(0);
                printf(" |");
            }
            else {
                printf("  %s |", board->shown[i][j]);
            }

        }
        printf("\n");
    }
    for (j = 0; j < c; j++) {
        printf("=====");
    }
    printf("=\n");
    printf("\n");
}

char* toString(int num) {
    int length = snprintf( NULL, 0, "%d", num );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", num );
    return str;
}


