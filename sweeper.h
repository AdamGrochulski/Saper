#ifndef _SWEEPER_H
#define _SWEEPER_H

#include "struct.h"

void gameEngine();
void commandPicker(Board *board, Pos *pos, int type);
void playerMove(Board *board, Pos *pos, int x, int y, int type);
void revealTiles(Board *board, int x, int y);
char* toString(int num);
void place_flag(Board *Board, Pos *pos, int x, int y);
char to_char(int number);
char *nametag();
void sync_flag(Board* Board, int count);
void result(Board* Board, int count);
#endif