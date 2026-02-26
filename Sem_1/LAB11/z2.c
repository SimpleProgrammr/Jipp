#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct MY_VECTOR {
    int dim; // rozmiar wektora
    char str[64]; // nazwa wektora
    double *buff; // tablica dla przechowywania wektora o rozmiarze dim
};

// a) Inicjowanie wektora
void init_vector(struct MY_VECTOR *vec) {
    vec->dim = 0;
    vec->str[0] = '\0';
    vec->buff = NULL;
}

// b) Przygotowanie wektora
int prepare_vector(struct MY_VECTOR *vec, int n, const char *name, char type) {
    vec->dim = n;
    strncpy(vec->str, name, 63);
    vec->str[63] = '\0';

    // Alokacja pamięci
    vec->buff = (double *) malloc(n * sizeof(double));
    if (vec->buff == NULL) {
        printf("Błąd alokacji pamięci dla wektora %s\n", name);
        return -1;
    }

    // Wypełnienie tablicy
    for (int i = 0; i < n; i++) {
        if (type == 'x') {
            vec->buff[i] = 1.0 / (i + 1); // xi = 1/(i+1)
        } else if (type == 'y') {
            vec->buff[i] = i + 1; // yi = i+1
        }
    }

    return 0;
}

// c) Algorytm mnożenia (iloczyn skalarny)
double dot_product(struct MY_VECTOR *x, struct MY_VECTOR *y) {
    if (x->dim != y->dim) {
        printf("Błąd: wektory mają różne wymiary!\n");
        return 0.0;
    }

    double dot = 0.0;
    for (int i = 0; i < x->dim; i++) {
        dot += x->buff[i] * y->buff[i];
    }

    return dot;
}

// d) Sprawdzenie poprawności wyniku
void verify_result(double dot, int n) {
    double expected = (double) n;
    double error = fabs(dot - expected);

    printf("\n=== Weryfikacja wyniku ===\n");
    printf("Obliczony iloczyn skalarny: %.10f\n", dot);
    printf("Oczekiwana wartość: %.10f\n", expected);
    printf("Błąd: %.10e\n", error);

    if (error < 1e-9) {
        printf("✓ Wynik POPRAWNY\n");
    } else {
        printf("✗ Wynik NIEPOPRAWNY\n");
    }
}

// e) Zwolnienie pamięci
void free_vector(struct MY_VECTOR *vec) {
    if (vec->buff != NULL) {
        free(vec->buff);
        vec->buff = NULL;
    }
    vec->dim = 0;
}

// Funkcja pomocnicza - wyświetlenie wektora
void print_vector(struct MY_VECTOR *vec, int max_elements) {
    printf("Wektor '%s' (dim=%d):\n", vec->str, vec->dim);
    int limit = (vec->dim < max_elements) ? vec->dim : max_elements;

    for (int i = 0; i < limit; i++) {
        printf("  %s[%d] = %.6f\n", vec->str, i, vec->buff[i]);
    }

    if (vec->dim > max_elements) {
        printf("  ... (pozostałe %d elementów)\n", vec->dim - max_elements);
    }
}

int main() {
    int n;

    printf("=== Obliczanie iloczynu skalarnego dwóch wektorów ===\n\n");
    printf("Podaj rozmiar wektorów n: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Błąd: rozmiar musi być dodatni!\n");
        return 1;
    }

    // Alokacja tablicy struktur
    struct MY_VECTOR *tab = (struct MY_VECTOR *) malloc(2 * sizeof(struct MY_VECTOR));
    if (tab == NULL) {
        printf("Błąd alokacji pamięci dla tablicy struktur!\n");
        return 1;
    }

    // a) Inicjowanie wektorów
    init_vector(&tab[0]);
    init_vector(&tab[1]);

    // b) Przygotowanie wektorów
    printf("\nPrzygotowanie wektorów...\n");
    if (prepare_vector(&tab[0], n, "x", 'x') != 0) {
        free(tab);
        return 1;
    }
    if (prepare_vector(&tab[1], n, "y", 'y') != 0) {
        free_vector(&tab[0]);
        free(tab);
        return 1;
    }

    // Wyświetlenie wektorów (maksymalnie 10 elementów)
    printf("\n");
    print_vector(&tab[0], 10);
    printf("\n");
    print_vector(&tab[1], 10);

    // c) Obliczenie iloczynu skalarnego
    printf("\nObliczanie iloczynu skalarnego...\n");
    double dot = dot_product(&tab[0], &tab[1]);
    printf("dot = x^T * y = %.10f\n", dot);

    // d) Weryfikacja wyniku
    verify_result(dot, n);

    // e) Zwolnienie pamięci
    printf("\nZwalnianie pamięci...\n");
    free_vector(&tab[0]);
    free_vector(&tab[1]);
    free(tab);

    printf("Program zakończony pomyślnie.\n");

    return 0;
}