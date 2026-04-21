#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROZMIAR 10
#define NAZWA_PLIKU "dane.bin"

// Funkcja wyświetlająca zawartość tablicy
void wyswietl_tablice(int *tablica, int rozmiar, const char *opis) {
    printf("%s\n", opis);
    printf("[");
    for (int i = 0; i < rozmiar; i++) {
        printf("%d", tablica[i]);
        if (i < rozmiar - 1) {
            printf(", ");
        }
    }
    printf("]\n\n");
}

// Funkcja zapisująca tablicę do pliku binarnego
int zapisz_do_pliku(const char *nazwa_pliku, int *tablica, int rozmiar) {
    FILE *plik = fopen(nazwa_pliku, "wb");
    if (plik == NULL) {
        printf("Błąd: Nie można otworzyć pliku '%s' do zapisu!\n", nazwa_pliku);
        return -1;
    }

    // Zapisanie rozmiaru tablicy
    fwrite(&rozmiar, sizeof(int), 1, plik);

    // Zapisanie danych tablicy
    size_t zapisane = fwrite(tablica, sizeof(int), rozmiar, plik);

    fclose(plik);

    if (zapisane != rozmiar) {
        printf("Błąd: Zapisano tylko %zu z %d elementów!\n", zapisane, rozmiar);
        return -1;
    }

    printf("✓ Zapisano %d elementów do pliku '%s'\n\n", rozmiar, nazwa_pliku);
    return 0;
}

// Funkcja wczytująca tablicę z pliku binarnego
int wczytaj_z_pliku(const char *nazwa_pliku, int *tablica, int rozmiar) {
    FILE *plik = fopen(nazwa_pliku, "rb");
    if (plik == NULL) {
        printf("Błąd: Nie można otworzyć pliku '%s' do odczytu!\n", nazwa_pliku);
        return -1;
    }

    // Odczytanie rozmiaru tablicy
    int rozmiar_z_pliku;
    fread(&rozmiar_z_pliku, sizeof(int), 1, plik);

    if (rozmiar_z_pliku != rozmiar) {
        printf("Ostrzeżenie: Rozmiar w pliku (%d) różni się od oczekiwanego (%d)!\n",
               rozmiar_z_pliku, rozmiar);
    }

    // Odczytanie danych tablicy
    size_t wczytane = fread(tablica, sizeof(int), rozmiar, plik);

    fclose(plik);

    if (wczytane != rozmiar) {
        printf("Błąd: Wczytano tylko %zu z %d elementów!\n", wczytane, rozmiar);
        return -1;
    }

    printf("✓ Wczytano %d elementów z pliku '%s'\n\n", rozmiar, nazwa_pliku);
    return 0;
}

// Funkcja zerująca tablicę
void wyzeruj_tablice(int *tablica, int rozmiar) {
    memset(tablica, 0, rozmiar * sizeof(int));
    printf("✓ Wyzerowano zawartość tablicy\n\n");
}

int main() {
    int tablica[ROZMIAR];

    printf("=== Program obsługi plików binarnych ===\n\n");

    // 1. Inicjalizacja tablicy przykładowymi wartościami
    printf("KROK 1: Inicjalizacja tablicy\n");
    for (int i = 0; i < ROZMIAR; i++) {
        tablica[i] = (i + 1) * 10; // Wartości: 10, 20, 30, ..., 100
    }
    wyswietl_tablice(tablica, ROZMIAR, "Tablica po inicjalizacji:");

    // 2. Zapis tablicy do pliku binarnego
    printf("KROK 2: Zapis tablicy do pliku binarnego\n");
    if (zapisz_do_pliku(NAZWA_PLIKU, tablica, ROZMIAR) != 0) {
        return 1;
    }

    // 3. Wyzerowanie zawartości tablicy
    printf("KROK 3: Zerowanie tablicy\n");
    wyzeruj_tablice(tablica, ROZMIAR);
    wyswietl_tablice(tablica, ROZMIAR, "Tablica po wyzerowaniu:");

    // 4. Wczytanie danych z pliku
    printf("KROK 4: Odczyt tablicy z pliku binarnego\n");
    if (wczytaj_z_pliku(NAZWA_PLIKU, tablica, ROZMIAR) != 0) {
        return 1;
    }

    // 5. Wyświetlenie odczytanych danych
    printf("KROK 5: Wyświetlenie odczytanych danych\n");
    wyswietl_tablice(tablica, ROZMIAR, "Tablica po wczytaniu z pliku:");

    printf("Program zakończony pomyślnie.\n");

    return 0;
}