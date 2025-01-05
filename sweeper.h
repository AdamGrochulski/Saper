#ifndef _SWEEPER_H
#define _SWEEPER_H

typedef struct {
    int x;
    int y;
} Pos;

void commandPicker(Pos *pos, int init);
void playerMove(Pos *pos, int x, int y);

#endif