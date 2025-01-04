#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 30 // Maksymalna dlugosc nazwy gracza

typedef struct scores{
  int score; //wynik gracza
  int level; //poziom trudnosci
  char *name; //nazwa uzytkownika
}highscore;

highscore* init() { // mallocuje pamieć dla structury highscore
  highscore* wynik = malloc(sizeof(highscore));
  wynik->name = malloc(MAXNAME * sizeof(char));
  return wynik;
}

void send_data(highscore *wynik, int score, int level, char *name){ //Przesyła dane użytkownika do structury highscore
  wynik->score = score;
  wynik->level = level;
  //dodac warunek z MAXNAME (albo tu, albo w main.c)
  wynik->name = name;
}

void write_and_save(highscore* wynik){ //funkcja zapisuje wyniki w pliku stats.txt
  FILE *file = fopen("stats.txt", "a");
  if(file == NULL){
    printf("Błąd podczas otwierania pliku \n");
  }
  if(wynik->name != NULL){
    fprintf(file, "%s %d %d\n", wynik->name, wynik->score, wynik->level);
  }
  fclose(file);
}

void free_structure(highscore* wynik){//zwalnia pamięć
  free(wynik->name);
  free(wynik);
}

//Plik stats.txt:
//[NAME] [SCORE] [LEVEL]
