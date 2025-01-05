#include "sweeper.h"
#include <stdlib.h>
#include <stdio.h>

void commandPicker(Pos *pos, int type) {
    char choice;
    int x,y;

    printf("Wprowadź komendę: ");
    scanf(" %c %d %d",&choice, &x,&y);
    
    if (type==1) {
        switch (choice) {
            case 'f':
            
                break;         
        }
    }
    else {
        if (choice=='f') {
            playerMove(pos,x,y);
        }
        else {
            printf("Pierwsze polecenie musi być wybraniem pola!\n");
            commandPicker(pos,0);
        }
    }
}


void playerMove(Pos *pos, int x, int y) {
    pos->x=x-1;
    pos->y=y-1;
}
    