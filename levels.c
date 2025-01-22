#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void iChooseYou(Board *board) {
    int choice;

    printf("Proszę wybrać poziom trudności:\n");
    printf("1. Łatwy (9x9 pól i 10 min)\n");
    printf("2. Średni (16x16 pól i 40 min)\n");
    printf("3. Trudny (16x30 pól i 99 min)\n");
    printf("4. Własna plansza (nxm pól i 25%% pól planszy to miny)\n");
    printf("Jaki poziom trudności wybierasz (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 0: //Sekretny poziom trudności
            printf("Wybrałeś sekretny poziom trudności!\n");
            printf("Twoja plansza ma wymiary 50x50 i 625 min\n");
            board->r=50;
            board->c=50;
            board->m=625;
            board->multiplier=4;
            break;      
        case 1: //Łatwy poziom trudności
            printf("Wybrałeś łatwy poziom trudności!\n");
            board->r=9;
            board->c=9;
            board->m=10;
            board->multiplier=1;
            break;
        case 2: //Średni poziom trudności
            printf("Wybrałeś średni poziom trudności!\n");
            board->r=16;
            board->c=16;
            board->m=40;
            board->multiplier=2;
            break;
        case 3: //Trudny poziom trudności
            printf("Wybrałeś trudny poziom trudności!\n");
            board->r=16;
            board->c=30;
            board->m=99;
            board->multiplier=3;
            break;
        case 4: //Własny poziom trudności
            printf("Wybraleś własną planszę!\n");
            printf("Podaj jej wymiary: ");
            scanf("%d %d", &board->r, &board->c);
            if(board->r > 8 && board->c > 8 && board->r < 50 && board->c < 50) {
                //System wyznaczania ilości min (25% wszystkich pól to miny)
                int tmp = board->r * board->c;
                board->m = 0.25 * tmp;

                //System wyznaczania mnożnika, sprawdzamy jak pole naszej planszy ma się do pól plansz z poziomów trudności
                if (tmp >= (16*30)) { board->multiplier = 3; } //Sprawdzam, czy pole większe równe polu trudnego poziomu
                else if(tmp >= (16*16)) { board->multiplier = 2; } //Sprawdzam, czy pole większe równe polu średniego poziomu
                else { board->multiplier = 1; } //Dla pozostałych przypadków multiplier = 1

                printf("Twoja plansza ma wymiary %dx%d i %d min!\n", board->r, board->c, board->m);
            } else { 
                printf("Długość i szerokość planszy musi być w zakresie [9,49]!\n");
                exit(0);
            } 
        default:
            printf("Error - niepoprawna składnia polecenia!\n");
            exit(0);
    } 
    
}