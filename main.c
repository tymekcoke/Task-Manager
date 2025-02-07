#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TYTUL 50
#define MAX_OPIS 200
#define MAX_ZADANIA 100

typedef struct {
    char tytul[MAX_TYTUL];
    char opis[MAX_OPIS];
    int priorytet; // 1 – wysoki, 2 – średni, 3 – niski
} Zadanie;

void dodajZadanieDoPliku(Zadanie zadania[], int *ilosc_zadan, const char *nazwa_pliku) {
    if (*ilosc_zadan >= MAX_ZADANIA) {
        printf("Osiągnięto maksymalną liczbę zadań\n");
        return;
    }

    Zadanie zadanie;
    FILE *plik = fopen(nazwa_pliku, "a");
    if (plik == NULL) {
        printf("Błąd: Nie można otworzyć pliku.\n");
        return;
    }

    printf("Podaj tytuł zadania: ");
    fgets(zadanie.tytul, MAX_TYTUL, stdin);
    zadanie.tytul[strcspn(zadanie.tytul, "\n")] = '\0';

    printf("Podaj opis zadania: ");
    fgets(zadanie.opis, MAX_OPIS, stdin);
    zadanie.opis[strcspn(zadanie.opis, "\n")] = '\0';
    
    if (strlen(zadanie.opis) == 0) {
        strcpy(zadanie.opis, "Bez opisu");
    }

    printf("Podaj priorytet (1-wysoki, 2-sredni, 3-niski): ");
    scanf("%d", &zadanie.priorytet);
    getchar(); 

    fprintf(plik, "%s|%s|%d\n", zadanie.tytul, zadanie.opis, zadanie.priorytet);
    fclose(plik);

    zadania[*ilosc_zadan] = zadanie;
    (*ilosc_zadan)++;

    printf("Zadanie zapisane do pliku i dodane do listy.\n");
}

void wgrajZadania(Zadanie zadania[], int *ilosc_zadan, const char *nazwa_pliku) {
    FILE *plik = fopen(nazwa_pliku, "r");
    if (plik == NULL) {
        printf("Brak zapisanych zadań lub błąd otwierania pliku.\n");
        return;
    }

    char linia[300];
    while (fgets(linia, sizeof(linia), plik) != NULL) {
        if (*ilosc_zadan >= MAX_ZADANIA) break; 

        Zadanie zadanie;
        if (sscanf(linia, "%49[^|]|%199[^|]|%d", zadanie.tytul, zadanie.opis, &zadanie.priorytet) == 3) {
            zadania[*ilosc_zadan] = zadanie;
            (*ilosc_zadan)++;
        }
    }

    fclose(plik);
    printf("Załadowano %d zadań z pliku.\n", *ilosc_zadan);
}

void wyswietlZadania(Zadanie zadania[], int ilosc_zadan) {
    if (ilosc_zadan == 0) {
        printf("Brak zapisanych zadań.\n");
        return;
    }

    printf("\nLista zadań:\n");
    for (int i = 0; i < ilosc_zadan; i++) {
        printf("Zadanie %d:\n", i + 1);
        printf("  Tytuł: %s\n", zadania[i].tytul);
        printf("  Opis: %s\n", zadania[i].opis);
        printf("  Priorytet: %d\n\n", zadania[i].priorytet);
    }
}

int main() {
    Zadanie *zadania = malloc(MAX_ZADANIA * sizeof(Zadanie));
    if (zadania == NULL) {
        printf("Błąd alokacji pamięci!\n");
        return 1;
    }

    int ilosc_zadan = 0;

    wgrajZadania(zadania, &ilosc_zadan, "zadania.txt");

    int wybor;
    do {
        printf("\nMENU:\n");
        printf("1. Dodaj zadanie\n");
        printf("2. Wyświetl zadania\n");
        printf("3. Wyjdź\n");
        printf("Twój wybór: ");
        scanf("%d", &wybor);
        getchar(); 

        switch (wybor) {
            case 1:
                dodajZadanieDoPliku(zadania, &ilosc_zadan, "zadania.txt");
                break;
            case 2:
                wyswietlZadania(zadania, ilosc_zadan);
                break;
            case 3:
                printf("Zamykanie programu...\n");
                break;
            default:
                printf("Niepoprawny wybór! Spróbuj ponownie.\n");
        }
    } while (wybor != 3);

    free(zadania);
    return 0;
}
