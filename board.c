#include <stdio.h>
#include <stdlib.h>
#include <time.h> //Używany, by wygenerować losowo bomby

#include "levels.h"
#include "board.h"
#include "sweeper.h"

//Notatki twórcze
//Wszystkie funkcje w board.c zostały zrobione zgodnie z planem
//-> implementacja board.c i board.h - Adam Grochulski
//-> wymyślenie algorytmu generowania planszy - Przemek Pindrala

void Colors(int type) {
    if (type == 0) //Zmiana koloru na domyślny (symbol 0 i tekst)
        printf("\033[0m");
    if (type == 1) //Zmiana koloru na niebieski (symbol 1)
        printf("\033[1;34m");
    if (type == 2) //Zmiana koloru na zielony (symbol 2)
        printf("\033[1;32m");
    if (type == 3) //Zmiana koloru na czerwony (symbol 3)
        printf("\033[1;31m");
    if (type >= 4) //Zmiana koloru na fioletowy (symbol 4-8)
        printf("\033[1;35m");
    if (type == -1) //Zmiana koloru na żółty (symbol bomby)
        printf("\033[1;33m");
}

void generatorForBoard(Board *board,Pos *pos) {
    //Funkcja iChooseYou z biblioteki levels.h pozwala graczowi wybrać poziom trudności
    iChooseYou(board);

    //Pierwszy input gracza, jako że pierwszy ruch narzuca nam wygląd planszy to w funkcji commandPicker zmienna type = 0
    commandPicker(board,pos,0);

    //Tworzenie naszej planszy (generowanie oznaczeń w każdej komórce planszy)
    createBoardData(board); //Przypisywanie pamięci do wszystkich argumentów struct Board * board

    firstInputPlacement(board, pos); //Wpisywanie pierwszego inputu gracza w dacie structa board
                                     //oraz oznaczanie miejsc wokół niego, jako takie, które nie mogą mieć bomb
    bombGeneration(board); //Losowe generowanie bomb na planszy
    
    bombCounter(board); //Zliczanie bomb w celu oznaczenia "wartości" każdego pola na planszy

    board->Run=0; //Zdefiniowanie, że gra jest w toku

    origin_sync(board);
}

Board * createBoardData(Board *board) {
    //Funkcja przypisuje pamięć dla tablicy z danymi oraz tablicy widocznej dla gracza
    int i,j;
    int r = board->r;
    int c = board->c;
    board->score = 0;

    board->data = (int**) malloc(sizeof(int*) * r);
    board->data_origin = (int**) malloc(sizeof(int*) * r);
    board->shown = (char***) malloc(sizeof(char**) * r);
    for (i=0; i < r; i++) {
        board->data[i] = (int*) malloc(sizeof(int)*c);
        board->data_origin[i] = (int*) malloc(sizeof(int)*c);
        board->shown[i] = (char**) malloc(sizeof(char*)*c);
    }
    //Tablice z danymi uzupełnia liczbą -3 (w kodzie oznacza liczbę, która nie została przetworzona)
    //oraz tablice widoczną dla gracza uzupełnia " " (nie odkryte pole)
    for (i=0; i < r; i++) {
        for (j=0; j < c; j++) {
            board->data[i][j]=-3;
            board->shown[i][j]=" ";
        }
    }
}

void firstInputPlacement(Board *board, Pos *pos) {
    //Funkcja, która zapisuje w tablicy z danymi pierwszy input gracza, jako 0
    //oraz pola wokół niego, jako -2 (w kodzie oznacza liczbę, która nie może być miną)
    int x = pos->x;
    int y = pos->y;

    aroundTheArea(board,x,y,0);

    board->data[x][y]=0; //Zapisanie pierwszego inputa gracza, jako 0
}

void bombGeneration(Board *board) {
    int i,j;
    int count = 0; //Licznik bomb używany, aby określić ile bomb zostało zapisanych już na tablicy
    unsigned int seed = time(0); //Wybranie losowe seeda bomb na podstawie czasu systemowego

    while (count<board->m) {
        i=rand_r(&seed) % board->r; //Przypisanie losowego pola [i,j], jako potencjalnego miejsca na bombę
        j=rand_r(&seed) % board->c;

        if (board->data[i][j] == -3) { //Sprawdzenie czy pole w tabeli danych planszy jest równe -3 (jest to pole na którym bomba może być)
            board->data[i][j]=-1; //Przypisanie bombie wartości -1 w tabeli z danymi
            count++;
        }
    }
}

void bombCounter(Board *board) {
    int i,j;
    int count; //Ilość bomb wokół pola [i,j]
    for (i=0; i < board->r; i++) {
        for (j=0; j < board->c; j++) {
            if (board->data[i][j] != -1) {
                count=aroundTheArea(board,i,j,1); //Funkcja aroundTheArea przyjmuje type=1, kiedy chcemy zliczyć bomby wokoł pola [i,j] 
                board->data[i][j]=count; //Zapisujemy w dacie, bo w końcu wartość każdego pola jest ilością bomb wokół niego
            }
        }       
    }
}

int aroundTheArea(Board *board, int x, int y, int type) {
    int i_around,j_around;
    int count=0; 
    //W tym fragmecie kodu poruszamy się wokół pola [x,y] ([x-1,y-1] [x,y-1] [x+1,y-1] itd.)
    for(j_around=y-1;j_around<=y+1;j_around++) {
        if (j_around>=0 && j_around<board->c) {
            for(i_around=x-1;i_around<=x+1;i_around++) {
                if (i_around>=0 && i_around<board->r) {
                    if (type == 0) { //Type 0 używamy przy tworzeniu tablicy, aby określić, że miejsca wokół pierwszego zaznaczego pola nie mogą być bombami
                        board->data[i_around][j_around]=-2; //Zapisujemy miejsce [i_around,j_around], jako -2 (nie może tu być miny)
                    }
                    if (type == 1) { //Type 1 używamy przy wyznaczaniu wartości poszczególnych pól na planszy
                        if (board->data[i_around][j_around] == -1)
                                    count+=1;
                    }
                }
            }
        }
    }
    if (type==0)
        return 0; //Zwracamy "symbolicznie" 0, ponieważ dla type=0 wartość funkcji nie jest używania
    if (type==1)
        return count; //Zwracamy liczbę bomb wokoł pola [x,y] 
}

void printBoard(Board *board) {
    int i,j;
    int r = board->r;
    int c = board->c;
    for (j = 0; j < c; j++) {
        if (j==0)
            printf("====");
        if (j+1<10) 
            printf("= 0%d ",j+1);
        else {
            printf("= %d ",j+1);
        }
    }
    printf("=\n");
    for (i=0;i<r;i++) {
        printf(" ");
        if (i+1<10)
            printf("0");
        printf("%d |",i+1);
        for (j = 0; j < c; j++) {
            if (contains_specific_letter(board->shown[i][j], ' ') -1 ) { // TU JEDNAK MUSI TO ZOSTAĆ (board->shown[i][j]!=" ")
                if (board->data[i][j] >= 0) {
                    Colors(board->data[i][j]);
                    printf("  %s", board->shown[i][j]);
                } 
                else if(contains_specific_letter(board->shown[i][j], 'F')){
                    printf("  F");    
                }
                else {  // TUUUUUTAJ TRZEBA ZMIENIC WARUNEK ZEBY DZIALALO Z FLAGAMI
                    Colors(-1);       
                    printf("  *");
                }
                Colors(0);
            }
            else {
                printf("  %s", board->shown[i][j]);
            }
            printf(" |");
        }
        printf("\n");
    }
    for (j = 0; j < c; j++) {
        if (j==0)
            printf("====");
        printf("=====");
    }
    printf("=\n");
    printf("\n");
}

void printBoardDebug(Board *board) {
    int i,j;
    int r = board->r;
    int c = board->c;
    for (j = 0; j < c; j++) {
        if (j==0)
            printf("====");
        if (j+1<10) 
            printf("= 0%d ",j+1);
        else {
            printf("= %d ",j+1);
        }
    }
    printf("=\n");
    for (i=0;i<r;i++) {
        printf(" ");
        if (i+1<10)
            printf("0");
        printf("%d |",i+1);
        for (j = 0; j < c; j++) {
            printf("  %d", board->data[i][j]);

            printf(" |");
        }
        printf("\n");
    }
    for (j = 0; j < c; j++) {
        if (j==0)
            printf("====");
        printf("=====");
    }
    printf("=\n");
    printf("\n");
}

//synchronizuje data i data_origin
void origin_sync(Board *board){
    for(int i = 0; i < board->r; i++){
        for(int j = 0; j < board->c; j++){
            board->data_origin[i][j] = board->data[i][j];
        }
    } 
}

int contains_specific_letter(const char *str, char letter) {
    while (*str) {
        if (*str == letter) {
            return 1;
        }
        str++;
    }
    return 0;
}



