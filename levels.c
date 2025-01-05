#include <stdio.h>
#include "board.h"

void iChooseYou(Board *board) {
    int choice;

    printf("Proszę wybrać poziom trudności:\n");
    printf("1. Łatwy (9x9 pól i 10 min)\n");
    printf("2. Średni (16x16 pól i 40 min)\n");
    printf("3. Trudny (16x30 pól i 99 min)\n");
    printf("Jaki poziom trudności wybierasz (1-3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Wybrałeś łatwy poziom trudności!\n");
            board->r=9;
            board->c=9;
            board->m=10;
            board->multiplier=1;
            break;
        case 2:
            printf("Wybrałeś średni poziom trudności!\n");
            board->r=16;
            board->c=16;
            board->m=40;
            board->multiplier=2;
            break;
        case 3:
            printf("Wybrałeś trudny poziom trudności!\n");
            board->r=16;
            board->c=30;
            board->m=99;
            board->multiplier=3;
            break;
    }

    
}