#ifndef _STRUCT_H
#define _STRUCT_H

typedef struct {
    int r,c; //Wielkość tablicy r(liczba wierszy) x c(liczba kolumn)
    int m; //Ilość min
    int **data; //Wartości każde pozycji na planszy sapera od (-1 - 8), gdzie -1 to bomba, 0 - 8 liczba bomb wokół danego pola
    int **data_origin;//////////////////////////////////////////////////////////////////////////////////////////////////////////teoretycznie mozna usunąc
    char **shown; //Wartości które są widoczne
    char **shown_origin;
    int multiplier; //Wartość mnożnika zależny od poziomu trudności (łatwy - 1, normalny - 2, trudny - 3)
    int Run; //Przyjmuje: 0 - gdy program MineSweeper działa, 1 - gdy gra się kończy (klikając bombę lub zapisując do pliku)
    int score;
} Board;

typedef struct {
    int x; //Numer wiersza pola wybranego przez gracza
    int y; //Numer kolumny pola wybranej przez gracza
} Pos;

#endif
