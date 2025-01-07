#ifndef _BOARD_H
#define _BOARD_H

typedef struct {
    int r,c; //Wielkość tablicy r(liczba wierszy) x c(liczba kolumn)
    int m; //Ilość min
    int **data; //Wartości każde pozycji na planszy sapera od (-1 - 8), gdzie -1 to bomba, 0 - 8 liczba bomb wokół danego pola
    char ***shown; //Wartości które są widoczne
    int multiplier; //Wartość mnożnika zależny od poziomu trudności (łatwy - 1, normalny - 2, trudny - 3)
    int Run; //Przyjmuje: 0 - gdy program MineSweeper działa, 1 - gdy gra się kończy (klikając bombę lub zapisując do pliku)

} Board;

void Colors(int type);
Board * generatorForBoard();
Board * createBoardData(Board *board);
void printBoard(Board *board);
char* toString(int num);


#endif