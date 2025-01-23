#include "sweeper.h"
#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char** argv) {
    int option;
    Colors(0); //Zamienie czcionki na bold na czas trwania całej gry.

    while(option = getopt(argc, argv, "pfh")) {
        switch(option) {
            case 'p':
                printf("Play\n");
                gameEngine();
                break;
            case 'f':
                FILE *file = argc > 2 ? fopen(argv[2],"r") : NULL;
                if(file == NULL) {
                    printf("Błąd podczas otwierania pliku!\n");
                    exit(0);
                }
                char buffer[100];
                while(fgets(buffer, sizeof(buffer), file))
                    printf("%s",buffer);
                break;
            case 'h':
                printf("Pomoc:\n");
                printf("-p -> uruchamia grę w trybie standardowym");
                printf("-f -> uruchamia grę zapisaną w pliku");
                printf("-h -> wyświetla instrukcje wywołania gry");
                break;
            default:
                printf("Koniec działania programu!\n");
                return 0;
            
        }
    }
    return 1;
}