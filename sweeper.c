#include "sweeper.h"
#include "board.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void commandPicker(Board *board, Pos *pos, int type) {
    char choice;
    int x,y;

    printf("Wprowadź komendę: ");
    scanf(" %c %d %d",&choice, &x,&y);
    
    if (type==1) {
            switch (choice) {
                case 'f':
                    playerMove(board,pos,x-1,y-1,0);
                    break;         
            }
            commandPicker(board, pos,1);
    }
    else {
        if (choice=='f') {
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
    int k,l;
    printf(board->shown[x][y]);
    if (board->data[x][y] == 0 && strcmp(board->shown[x][y]," ") == 0) {
        board->shown[x][y]=toString(board->data[x][y]);
        for(k=y-1;k<=y+1;k++) {
            if (k>=0 && k<board->c) {
                for(l=x-1;l<=x+1;l++) {
                    if (l>=0 && l<board->r) {
                        if (board->data[l][k] != -1) {
                            printf("l: %d k: %d ",l,k);
                            printf(" \n");
                            revealTiles(board,l,k);
                            board->shown[l][k] = toString(board->data[l][k]);
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
    revealTiles(board,x,y);
    printBoard(board);
}       
    