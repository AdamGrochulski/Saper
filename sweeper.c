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
    //printBoardDebug(board);

    while (board->Run==0) {
        commandPicker(board, pos,1);
        printf("score: %d\n", board->score); // TO JEST TYLKO POD PODGLĄD
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
                case 'r': //Odsłanianie pola
                    playerMove(board,pos,x-1,y-1,0);
                    break;
                case 'f': //Stawianie flagi
                    place_flag(board,pos,x-1,y-1);
                    break;
                default:
                    printf("Niepoprawna komenda!\n");
                    break;

            }
    }
    else { //Przypadek, gdy gracz się rusza po raz pierwszy (konieczny dla wygenerowania tablicy)
        if (choice=='r') {
            pos->x=x-1;
            pos->y=y-1;
        }
        else {
            printf("Pierwsze polecenie musi być wybraniem pola!\n"); //Jeśli nie została wybrana komenda 'r' to wtedy prosimy jeszcze raz
            commandPicker(board, pos,0);
        }
    }
}
//Funkcja odsłaniająca pola po ruchu gracza
void revealTiles(Board *board, int x, int y) {
    int i_around,j_around;
    //Przejscie po polach wokół pola [x,y], jeśli jest puste
    if (board->data[x][y] == 0 && board->shown[x][y] == ' ') {
        board->shown[x][y]=to_char(board->data[x][y]);
        for(j_around=y-1;j_around<=y+1;j_around++) {
            if (j_around>=0 && j_around<board->c) {
                for(i_around=x-1;i_around<=x+1;i_around++) {
                    if (i_around>=0 && i_around<board->r) {
                        //Sprawdzanie czy pole wokół pola [x,y] nie jest miną
                        if (board->data[i_around][j_around] != -1) {
                            revealTiles(board,i_around,j_around); //Rekurencyjne sprawdzanie następnych pól wokół [i_around,j_around]
                            board->shown[i_around][j_around] = to_char(board->data[i_around][j_around]);
                        }
                    }
                }
            }
        }
    }
    // Gdy pole jest już odslonięte to po prostu je jeszcze raz "pokaż" (zabieg zrobiony w celu uniknięcia błędów)
    else {
        board->shown[x][y]=to_char(board->data[x][y]);
    }
}

//Funckja ruchu gracza, sprawdza czy pole jest bombą, jeśli nie, to odkrywa następne pola. W przeciwnym przypadku gra się kończy
void playerMove(Board *board, Pos *pos, int x, int y, int type) {
    pos->x=x;
    pos->y=y;
    if (board->data[x][y] != -1) {
        revealTiles(board,x,y);
    }
    else {
        board->shown[x][y]=to_char(board->data[x][y]);
        board->Run=1;
    }
    printBoard(board);
}       
//Funckja pomocniczna która zamienia integer na string
char* toString(int num) {
    int length = snprintf( NULL, 0, "%d", num );
    char* str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", num );
    return str;
}

void place_flag(Board *board, Pos *pos, int x, int y){
    if(board->shown[x][y] == 'F'){
        if(board->shown[x][y] == 'F' && board->data[x][y] == -1){
            board->shown[x][y] = ' ';
            board->score--;
        }
        else if (board->shown[x][y] == 'F' && board->data[x][y] != -1){
            board->shown[x][y] = ' ';
            board->score++;
        }
        else if ( board->shown[x][y] == 'F' && board->data[x][y] != -1){
            board->shown[x][y] = ' ';
            board->score++;
        }
        // else{
        //     board->shown[x][y] = board->shown_origin[x][y];
        // }
    }
    else if(board->shown[x][y] == ' '){
        board->shown[x][y] = 'F';
        if(board->shown[x][y] == 'F' && board->data[x][y] == -1){
            board->score++;
        }
        else if(board->shown[x][y] == 'F'&& board->data[x][y] != -1){
            board->score--;
        }
    }
    else{
        printf("Nie można ustawić flagi na odkrytm miejscu!\n");
    }
    printBoard(board);
}

char to_char(int number) {
    if (number >= 0 && number <= 9) {
        return (char)(number + '0');
    }
    return '\0';
}
