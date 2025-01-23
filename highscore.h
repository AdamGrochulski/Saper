#ifndef _HIGHSCORE_H
#define HIGHSCORE_H

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 30 // Maksymalna długość nazwy gracza
#define BUFSIZE 100 // Maksymalna długość linii w pliku stats.txt
#define STATS "stats.txt" // Plik do zapsywania danych

// Plik stats.txt:
// [NAME] [SCORE] [LEVEL]

highscore* init();

void send_data(highscore* wynik, int score, int level, char* name);

void write_and_save(highscore* wynik);

char *read_and_return(char* stats, int k, char* buffer);

int number_of_lines(char *stats);

int check_score(char* buffer);

void find_the_best(int i_arr[], int n, int index[]);

void print_leaderboard();

void free_structure(highscore* wynik);

void print_score(int score, int level, char *name);

#endif
