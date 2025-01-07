#ifndef _SWEEPER_H
#define _SWEEPER_H

#include "board.h"

typedef struct {
    int x;
    int y;
} Pos;

void commandPicker(Board *board, Pos *pos, int type);
void playerMove(Board *board, Pos *pos, int x, int y, int type);
void revealTiles(Board *board, int x, int y);

#endif