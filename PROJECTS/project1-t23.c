#include <float.h>
#include <stdio.h>
//#include <tgmath.h>
#include <math.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
#include <windows.h>


void clearStdin();


enum STOP_REASON { MAX_M, MAX_DEF_PRECISION, ABNORMAL, BOTH_MAX };

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


long double ff(long double x, long double delta_y, int M, int *stop_res, int *used_M) {
    long double y = x;
    long double element;
    int u_M = 0;
    int iteration = 2;
    do {
        element = pow(-1, iteration-1) * (pow(x, iteration) / iteration);
        y += element;
        u_M++;
    } while (fabs(element) > delta_y && iteration++ <= M);
    if (fabs(element) < delta_y) {
        *stop_res = MAX_DEF_PRECISION;
    }
    if (iteration > M) {
        *stop_res = MAX_M;
    }
    if (iteration > M && fabs(element) < delta_y)
        *stop_res = BOTH_MAX;
    *used_M = u_M;
    return y;
}

int main() {
    //ln(1+x) // -1 < x <= 1 // x - x^2/2 + x^3/3 - x^4/4 + ...
    //Wczytaj przedział
    //wczytaj ilość podziałów
    //Spradz czy delta nie jest < 1e-14

    setlocale(LC_ALL, "pl_PL.UTF-8");
    setlocale(LC_NUMERIC, "C");
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);



    long double a = 0, b = 0, nc = 0, deltaY = 0;
    long long int n = 0;
    printf("Liczymy Ln(1+x) !!!");
    printf("Interpretacja zakresu:\n---<A------B>--->x\n");
    printf("A <= x <= B\nZakres musi znajdować się w przedziale -1 < x <= 1\n"
        "Używaj kropek jako punktora w liczbach rzeczywistych, znaki po przeciku zostaną zignorowane\n");


    printf("Podaj początek zakresu (A): ");
    fflush(stdin);
    if (scanf("%Lf", &a) != 1 || a <= -1 || a > 1 || isnan(a)) {
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


    printf("Podaj ilość podziałów (1 <= N <= %d; Liczba calkowita): ", INT_MAX);
    if (scanf("%Le", &nc) != 1 || nc <= 0 || round(nc) != nc || isnan(nc) || nc > INT_MAX) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    n = safe_convert(nc);
    if (n < 1) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();
    long double deltaX = 0;
    if (n > 1)
        deltaX = (b - a) / (long double) (n-1);
    else
        deltaX = (b - a);
    if (deltaX < LDBL_EPSILON) {
        fprintf(stderr, "Zbyt gęsty podział dla zadanego zakresu\n");
        return 300;
    }


    printf("Podaj dokładność wyników (0 < DeltaY < 1e-16; liczba rzeczywista): ");
    if (scanf("%Le", &deltaY) != 1 || deltaY < 1e-16 || isnan(deltaY) || isinf(deltaY)) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    clearStdin();





    int M = 1;
    long double Mle = 0.0;
    printf("Podaj maksymalną ilość iteracji (0 < M < %d; ; Liczba całkowita): ", INT_MAX);
    if (scanf("%Le", &Mle) != 1 || Mle <= 0 || round(Mle) != Mle || isnan(Mle) || Mle > INT_MAX) {
        fprintf(stderr, "Błędne dane wejściowe\n");
        return 400;
    }
    M = safe_convert(Mle);
    if (M < 0) {
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

    printf("Lp.\t\tX\t\t\t\tf_szereg(X)\t\t\t\t f_ściśle(X)\t\t\t  Wyrazy_szeregu\t\t\tPowód zatrzymania\n");
    fprintf(file, "Lp.\t\tX\t\t\t\tf_szereg(X)\t\t\t\t f_ściśle(X)\t\t\t  Wyrazy_szeregu\t\t\tPowód zatrzymania\n");
    long double x = a;
    for (long long counter = 1; counter <= n; counter++) {
        int stop_res = ABNORMAL;
        int used_M = 0;
        long double f_x = ff(x, deltaY, M, &stop_res, &used_M);
        //stop_res = ABNORMAL;
        char *stop_msg;
        switch (stop_res) {
            case MAX_M:
                stop_msg = "Osiągnięto maksymalną ilość iteracji";
                break;
            case MAX_DEF_PRECISION:
                stop_msg = "Osiągnieto żadaną dokładność";
                break;
            case BOTH_MAX:
                stop_msg = "Osiągnięto maksymalną ilość iteracji i maksymalną precyzję";
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

        if (counter % (n > 100 ? n/100 : 1) == 0)
               printf("%-7lld %-15.6Le %-24.16Lg %-24.16Lg %-10d \t\t\t\t%s\n", counter, x, f_x, logl(1 + x), used_M, stop_msg);
        fprintf(file, "%-7lld %-15.6Le %-24.16Lg %-24.16Lg %-10d \t\t\t\t%s\n", counter, x, f_x, logl(1 + x), used_M, stop_msg);

        x += deltaX;
    }

    fclose(file);
}

void clearStdin() {
    while (getchar() != '\n');
}
