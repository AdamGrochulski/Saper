#include "highscore.h"

//Alokuje pamieć dla structury highscore
highscore* init() {
    highscore* wynik = malloc(sizeof(highscore));
    wynik->name = malloc(MAXNAME * sizeof(char));
    return wynik;
}

// Przesyła dane użytkownika do struktury highscore
void send_data(highscore* wynik, int score, int level, char* name) {
    wynik->score = score;
    wynik->level = level;
    strncpy(wynik->name, name, MAXNAME - 1);
    wynik->name[MAXNAME - 1] = '\0';
}

// Zapisuje wyniki do pliku stats.txt
void write_and_save(highscore* wynik) {
    FILE *file = fopen("stats.txt", "a");
    if (wynik->name != NULL) {
        fprintf(file, "%s %d %d\n", wynik->name, wynik->score, wynik->level);
    }
    fclose(file);
}

// Czyta plik i zwraca k-tą linię
char *read_and_return(char* stats, int k, char* buffer) {
    int i = 0;
    FILE* file = fopen(stats, "r");
    while (fgets(buffer, BUFSIZE, file) != NULL) {
        if (i == k) {
            break;
        }
        i++;
    }
    fclose(file);
    return buffer;
}

// Zwraca ilośc linii w pliku
int number_of_lines(char *stats) {
    int n = 0;
    char buffer[BUFSIZE];
    FILE* file = fopen(stats, "r");
    while (fgets(buffer, BUFSIZE, file) != NULL) {
        n++;
    }
    fclose(file);
    return n;
}

// Sprawdza wynik gracza w linii
int check_score(char* buffer) {
    int i = 0;
    char *ptr = NULL;

    while (buffer[i] != '\n' && buffer[i] != '\0') {
        if (buffer[i] == ' ' && buffer[i + 1] >= '0' && buffer[i + 1] <= '9') {
            ptr = buffer + i + 1;
            break;
        }
        i++;
    }
    return atoi(ptr);
}

// Szuka najlepszych wyników graczy
void find_the_best(int i_arr[], int n, int index[]) {
    int top_5[5] = {-1, -1, -1, -1, -1};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            if (i_arr[i] > top_5[j]) {
                for (int k = 4; k > j; k--) {// przesuwanie wartości w prawo
                    top_5[k] = top_5[k - 1];
                    index[k] = index[k - 1];
                }
                top_5[j] = i_arr[i];
                index[j] = i;
                break;
            }
        }
    }
}

// Drukuje tablicę 5 najlepszych wyników
void print_leaderboard() {
    int n = number_of_lines(STATS);
    int index[5] = {-1, -1, -1, -1, -1};
    char* buffer = malloc(BUFSIZE * sizeof(char)); 
    char** c_arr = malloc(n * sizeof(char*));
    int* i_arr = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        c_arr[i] = malloc(BUFSIZE * sizeof(char));
        read_and_return(STATS, i, buffer);
        strcpy(c_arr[i], buffer);
        i_arr[i] = check_score(buffer);
        }
    find_the_best(i_arr, n, index);

    printf("===== LEADERBOARD =====\n");
    for (int t = 0; t < 5; t++) {
        if (index[t] != -1) { // Sprawdza, czy indeks jest prawidłowy
            printf("%d. %s", t + 1, c_arr[index[t]]); // Dodanie numeru ranku
        }
    }

    for (int i = 0; i < n; i++) {
        free(c_arr[i]);
    }
    free(c_arr);
    free(i_arr);
    free(buffer);
}

// Zwalnia pamięć zaalokowaną dla struktury highscore
void free_structure(highscore* wynik) {
    free(wynik->name);
    free(wynik);
}

/*
int main() {
    int score = 4000;
    int level = 3;
    char name[] = "Pan Dziekan";

    highscore* wynik = init();

    send_data(wynik, score, level, name);
    write_and_save(wynik);
    free_structure(wynik);
    print_leaderboard();
    return 0;
}
*/
