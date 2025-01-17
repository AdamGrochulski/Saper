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
void origin_sync(Board *board);
void shown_origin_sync(Board *board);
int contains_specific_letter(const char *str, char letter);

#endif