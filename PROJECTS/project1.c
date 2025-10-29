#include <float.h>
#include <stdio.h>
#include <tgmath.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

void clearStdin();


enum STOP_REASON { MAX_M, MAX_DEF_PRECISION, ABNORMAL };

long long int safe_convert(long double ld) {
    // Check if value is within range
    if (ld > LLONG_MAX || ld < LLONG_MIN) {
        printf("Error: Value out of range\n");
        exit(300); // or handle error appropriately
    }

    // Check for NaN or infinity
    if (isnan(ld) || isinf(ld)) {
        printf("Error: Invalid value (NaN or Inf)\n");
        exit(300);
    }

    return (long long int) ld;
}


long double f(long double x, long double delta_y, int M, int *stop_res, int *used_M) {
    long double y = x;
    long double element;
    int u_M = 0;
    int iteration = 2;
    do {
        element = pow(-1, iteration-1) * (pow(x, iteration) / iteration);
        y += element;
        u_M++;
    } while (fabs(element) > delta_y && ++iteration <= M);
    if (fabs(element) < delta_y) {
        *stop_res = MAX_DEF_PRECISION;
    }
    if (iteration > M) {
        *stop_res = MAX_M;
    }
    *used_M = u_M;
    return y;
}

int main() {
    //ln(1-x) // -1 < x <= 1 // x - x^2/2 + x^3/3 - x^4/4 + ...
    //Wczytaj przedział
    //wczytaj ilość podziałów
    //Spradz czy delta nie jest < 1e-14

    setlocale(LC_ALL, "pl_PL.CP1250");

    long double a = 0, b = 0, nc = 0, deltaY = 0;
    long long int n = 0;
    printf("Liczymy Ln(1+x) !!!");
    printf("Interpretacja zakresu:\n---(A------B>--->x\n");
    printf("A < x <= B\nZakres musi znajdować się w przedziale -1 < x <= 1\n");
    printf("Podaj początek zakresu (A): ");

    if (scanf("%Le", &a) != 1 || a < -1 || a > 1 || isnan(a)) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();
    printf("Podaj koniec zakresu (B): ");
    if (scanf("%Le", &b) != 1 || b < -1 || b > 1 || b <= a || isnan(b)) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();
    printf("Podaj ilość podziałów (0 < N < %d): ",INT_MAX);
    if (scanf("%Le", &nc) != 1 || nc <= 0 || round(nc) != nc) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();
    printf("Podaj dokładność wyników (0 < DeltaY < 1e-16): ");
    if (scanf("%Le", &deltaY) != 1 || deltaY < 1e-16 || isnan(deltaY) || isinf(deltaY)) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();
    n = safe_convert(nc);
    if (n < 0) {
        printf("Błędne dane wejściowe\n");
    }
    long double deltaX = (b - a) / (long double) n;
    if (deltaX < LDBL_EPSILON) {
        fprintf(stderr, "Zbyt gęsty podział\n");
        return 300;
    }
    int M = 1000000000;
    printf("Podaj maksymalną ilość iteracji (0 < M < %d): ", INT_MAX);
    if (scanf("%d", &M) != 1 || M <= 0 || isnan(M) || isinf(M) || M > INT_MAX) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();


    FILE *file = NULL;
    file = fopen("Project_1.txt", "w");

    if (file == NULL) {
        fprintf(stderr, "Błąd pliku!\n");
        exit(404);
    }

    printf("Lp.\t\tX\t\t\t\tf_szereg(X)\t\t\t\tf_ściśle(X)\t\t\t\tWyrazy_szeregu\t\t\t\tPowód zatrzymania\n");
    fprintf(file, "Lp.\t\tX\t\t\t\tf_szereg(X)\t\t\t\tf_ściśle(X)\t\t\t\tWyrazy_szeregu\t\t\t\tPowód zatrzymania\n");
    long double x = a + deltaX;
    for (long long counter = 1; counter <= n; counter++) {
        int stop_res = ABNORMAL;
        int used_M = 0;
        long double f_x = f(x, deltaY, M, &stop_res, &used_M);
        //stop_res = ABNORMAL;
        char *stop_msg;
        switch (stop_res) {
            case MAX_M:
                stop_msg = "Osiągnięto maksymalną ilość iteracji";
                break;
            case MAX_DEF_PRECISION:
                stop_msg = "Osiągnieto żadaną dokładność";
                break;
            default:
                stop_msg = "Praca nie spodziewana";
                fprintf(stderr, "%s\n"
                        "Użyte M = %d\n"
                        "M = %d\n"
                        "X = %.10Lg\n"
                        "F(x) = %.10Lg\t->\tln(1+x) = %.10Lg\n"
                        "N = %lld\n"
                        "Delta X = %.10Lg\n"
                        "Delta Y = %.10Lg\n\n", stop_msg, used_M, M, x, f_x, log(1+x), n, deltaX, deltaY);
                exit(123);
        }

        printf("%-5lld %-15.6Le %-24.16Lg %-24.16Lg %-10d \t\t\t\t%s\n", counter, x, f_x, logl(1 + x), used_M,
               stop_msg);
        fprintf(file, "%-5lld %-15.6Le %-24.16Lg %-24.16Lg %-10d \t\t\t\t%s\n", counter, x, f_x, logl(1 + x), used_M,
                stop_msg);

        x += deltaX;
    }

    fclose(file);
}

void clearStdin() {
    while (getchar() != '\n');
}
