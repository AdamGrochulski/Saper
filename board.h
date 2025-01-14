#ifndef _BOARD_H
#define _BOARD_H

#include "struct.h"

void Colors(int type);
void generatorForBoard(Board *board,Pos *pos);
Board * createBoardData(Board *board);
void firstInputPlacement(Board *board, Pos *pos);
void bombGeneration(Board *board);
void bombCounter(Board *board);
int aroundTheArea(Board *board, int x, int y, int type);
void printBoard(Board *board);
void printBoardDebug(Board *board);

#endif