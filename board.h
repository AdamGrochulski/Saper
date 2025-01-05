#ifndef _BOARD_H
#define _BOARD_H

typedef struct {
    int r,c; //Wielkość tablicy r(liczba wierszy) x c(liczba kolumn)
    int m; //Ilość min
    int **data; //Wartości każde pozycji na planszy sapera od (-1 - 8), gdzie -1 to bomba, 0 - 8 liczba bomb wokół danego pola
    int multiplier; //Wartość mnożnika zależny od poziomu trudności (łatwy - 1, normalny - 2, trudny - 3)

} Board;

Board * generatorForBoard();
Board * createBoardData(Board *board);
void printBoard(Board *board);


#endif