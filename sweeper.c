#include "sweeper.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gameEngine() {
    //Przypisywania pamięci do struct board oraz struct pos
    Board * board = (Board*) malloc(sizeof(Board));
    Pos * pos = (Pos*) malloc(sizeof(Pos));

    //Funkcja generująca plansze
    generatorForBoard(board,pos);

    //Rozgrywka
    revealTiles(board,pos->x,pos->y);
    printBoard(board);

    while (board->Run==0) {
        commandPicker(board, pos,1);
    }
    free(board);
    free(pos);
}
void commandPicker(Board *board, Pos *pos, int type) {
    char choice;
    int x,y;

    printf("Wprowadź komendę: ");
    scanf(" %c %d %d",&choice, &x,&y);
    
    if (type==1) {
            switch (choice) {
                case 'r':
                    playerMove(board,pos,x-1,y-1,0);
                    break;         
            }
    }
    else {
        if (choice=='r') {
            pos->x=x-1;
            pos->y=y-1;
        }
        else {
            printf("Pierwsze polecenie musi być wybraniem pola!\n");
            commandPicker(board, pos,0);
        }
    }
}
void revealTiles(Board *board, int x, int y) {
    int i_around,j_around;
    if (board->data[x][y] == 0 && strcmp(board->shown[x][y]," ") == 0) {
        board->shown[x][y]=toString(board->data[x][y]);
        for(j_around=y-1;j_around<=y+1;j_around++) {
            if (j_around>=0 && j_around<board->c) {
                for(i_around=x-1;i_around<=x+1;i_around++) {
                    if (i_around>=0 && i_around<board->r) {
                        if (board->data[i_around][j_around] != -1) {
                            revealTiles(board,i_around,j_around);
                            board->shown[i_around][j_around] = toString(board->data[i_around][j_around]);
                        }
                    }
                }
            }
        }
    }
    else {
        board->shown[x][y]=toString(board->data[x][y]);
    }
}

void playerMove(Board *board, Pos *pos, int x, int y, int type) {
    pos->x=x;
    pos->y=y;
    if (board->data[x][y] != -1) {
        revealTiles(board,x,y);
    }
    else {
        board->shown[x][y]=toString(board->data[x][y]);
        board->Run=1;
    }
    printBoard(board);
}       

char* toString(int num) {
    int length = snprintf( NULL, 0, "%d", num );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", num );
    return str;
}