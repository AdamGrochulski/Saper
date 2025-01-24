#include "sweeper.h"
#include "board.h"
#include "highscore.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void gameEngine(FILE *file) {
    //Przypisywania pamięci do struct board oraz struct pos
    Board * board = (Board*) malloc(sizeof(Board));
    Pos * pos = (Pos*) malloc(sizeof(Pos));
    int count = 0;
    
    if(file == NULL) {
        //Funkcja generująca plansze
        generatorForBoard(board,pos);
        //Rozgrywka
        revealTiles(board,pos->x,pos->y);
        printBoard(board);
        printBoardDebug(board);
        board->flag_remain = board->m;
        while (board->Run==0) {
            commandPicker(board, pos, 1);
            sync_flag(board, count);
        }
    } else {
        //Gra z pliku
        count = generatorFromFile(board,pos,file);
    }
    result(board, count);
    if(board->win == 1){
        char* name = nametag();
        print_score(board->score, board->multiplier, name);
        free(name);
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
            commandPicker(board, pos, 0);
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
    if(board->flag_remain > 0 && board->flag_remain <= board->m)
        if(board->shown[x][y] == 'F'){
            if(board->shown[x][y] == 'F' && board->data[x][y] == -1){
                board->shown[x][y] = ' ';
                //board->score--;
            }
            else if (board->shown[x][y] == 'F' && board->data[x][y] != -1){
                board->shown[x][y] = ' ';
                //board->score++;
            }
            else if ( board->shown[x][y] == 'F' && board->data[x][y] != -1){
                board->shown[x][y] = ' ';
                //board->score++;
            }
            // else{
            //     board->shown[x][y] = board->shown_origin[x][y];
            // }
        }
        else if(board->shown[x][y] == ' '){
            board->shown[x][y] = 'F';
            if(board->shown[x][y] == 'F' && board->data[x][y] == -1){
                //board->score++;
            }
            else if(board->shown[x][y] == 'F'&& board->data[x][y] != -1){
                //board->score--;
            }
        }
        else{
            printf("Nie można ustawić flagi na odkrytm miejscu!\n");
        }
    else{
        printf("Nie można postawić flagi, limit flag został wyczerpany.\n");
    }
    printBoard(board);
}

// funkcja, syncująca czy flagi sa w miejscu bomby
// jesli tak to break
void sync_flag(Board *board, int count){
    count = 0;
    board->flag_remain = board->m;
    for(int i = 0; i < board->r; i++){
        for(int j = 0; j < board->c; j++){
            if(board->shown[i][j] == 'F' && board->data[i][j] == -1){
                count++;
            }
        }
    }
    for(int i = 0; i < board->r; i++){
        for(int j = 0; j < board->c; j++){
            if(board->shown[i][j] == 'F'){
                board->flag_remain--;
            }
        }
    }
    //printf("score: %d\n", count); // TO JEST TYLKO POD PODGLĄD
    printf("Flagi do użycia: %d\n", board->flag_remain); // TO JUŻ POWINNO BYC
    if(count == board->m){
        board->Run = 1;
        board->win = 1;
    }
    board->score = count;
}


char to_char(int number) {
    if (number >= 0 && number <= 9) {
        return (char)(number + '0');
    }
    return '\0';
}

char *nametag() {
    char *name = malloc(32);
    int valid_input = 0;
    while (!valid_input) {
        printf("Wprowadź swoją nazwę gracza: ");
        if (scanf("%31s", name) == 1) { 
            valid_input = 1;
        }
    }
    return name;
}

void result(Board* board, int count){
    if(board->win == 1){
       printf("You won!\n");
    }
    else{
        printf("Game over!\n");
    }
}