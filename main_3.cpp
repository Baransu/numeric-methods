#include <cstdio>
#include <cmath>

using namespace std;

const double TOLX = 10e-16; // zadana tolerancja bledu
const double TOLF = 10e-16; // zadana tolerancja residuum
const int MAX_ITER = 1000;

const double X_0 = 0.4;

void header() {
    printf("n:   x:              residuum:       estymator: \n");
}

const char * STEP_FORMAT = "%2d %15e,%15e,%15e \n";

// Residuum |f(x)| - wartość bezwględna wartości funkcji w punkcie 

// https://www.wolframalpha.com/input/?i=sin%5E2(x+%2F+4.0)+-+x
double funkcja_a(double x) {
    return sin(x / 4.0) * sin(x / 4.0) - x;
}

double funkcja_a_pochodna(double x) {
    return (sin(x / 2.0) - 4.0) / 4.0;
}

double funkcja_a_phi(double x) {
    return sin(x / 4.0) * sin(x / 4.0);
}

// https://www.wolframalpha.com/input/?i=tan(2+*+x)+-+x+-+1.0
double funkcja_b(double x) {
    return tan(2 * x) - x - 1.0;
}

double funkcja_b_pochodna(double x) {
    return 2 / (cos(2 * x) * cos(2 * x));
}

double funkcja_b_phi(double x) {
    return atan(x + 1) / 2;
}

// estymator > TOLX -> Kryterium dokładności wyznaczenia xn
// fabs(y) > TOLF   -> Kryterium wiarygodności xn jako przybliżenie pierwiastka
// i < NMAX         -> Arbitralna maksymalna ilość iteracji

// estymator dla wszystkich metod poza bisekcji
// en = x_n - x_n_1

void newton(double (*func)(double), double (funcPoch)(double)) {
    double x = X_0, previous_x, f_x = 1.0, estymator = 1.0, residuum = 1.0;
    int i = 0;

    printf("Metoda Newtona:\n");
    header();

    while ((estymator > TOLX || residuum > TOLF) && i < MAX_ITER) {
        i++;
        previous_x = x;
        x -= func(x) / funcPoch(x);
        f_x = func(x);
        estymator = fabs(previous_x - x);
        residuum = fabs(f_x);
        printf(STEP_FORMAT, i, x, residuum, estymator);
    }
    printf("\n");
}

const double X_1 = 2.0;

void sieczne(double (*func)(double)) {
    double x = X_1, x_previous = X_0, temp_x, f_x = 1.0, estymator = 1.0, residuum = 1.0;
    int i = 0;

    printf("Metoda siecznych:\n");
    header();

    while ((estymator > TOLX || residuum > TOLF) && i < MAX_ITER) {
        i++;
        f_x = func(x);
        temp_x = x;
        x -= (f_x / ((f_x - func(x_previous)) / (x - x_previous)));
        x_previous = temp_x;
        estymator = fabs(x_previous - x);
        residuum = fabs(f_x);
        printf(STEP_FORMAT, i, x, residuum, estymator);
    }
    printf("\n");
}

// z cwiczen oba przeksztalcenia dla metody picatda sa zbiezne
void picard(double (*fun)(double)) {
    int i = 0;
    double x = X_0, f_x = 1.0, estymator = 1.0, residuum = 1.0;

    printf("Metoda Picarda:\n");
    header();

    while ((estymator > TOLX || residuum > TOLF) && i < MAX_ITER) {
        i++;
        f_x = fun(x);
        estymator = fabs(x - f_x);
        residuum = fabs(f_x);
        x = f_x;
        printf(STEP_FORMAT, i, x, residuum, estymator);
    }
    printf("\n");
}


const double A_0 = -0.5;
const double B_0 = 0.5;

void bis(double (*func)(double)) {
    int i = 0;
    double x = X_0, f_x = 1, estymator, a, an = A_0, b, bn = B_0, residuum;

    printf("Metoda bisekcji:\n");
    header();
    
    do {
        i++;

        // Estymator bledu bisekcji - połowa przedziału
        estymator = (bn - an) / 2.0;

        f_x = func(x);

        a = func(an);
        b = func(bn);

        // sprawdzenie która polowa [a,x][x,b] posiada zmiane znaku
        if (f_x * a < 0) {
            bn = x;
        } else if (f_x * b < 0) {
            an = x;
        }

        x = (an + bn) / 2.0;

        residuum = fabs(f_x);
        printf(STEP_FORMAT, i, x, fabs(f_x), estymator);
    } while ((estymator > TOLX || residuum > TOLF) && i < MAX_ITER);
    printf("\n");
}


int main() {
    printf("\nFunkcja nr 1: sin(x/4)^2 - x = 0\n\n");

    picard(funkcja_a_phi);
    bis(funkcja_a);
    newton(funkcja_a, funkcja_a_pochodna);
    sieczne(funkcja_a);

    printf("Funkcja nr 2: tan(2x) - x - 1 = 0\n\n");

    picard(funkcja_b_phi);
    bis(funkcja_b);
    newton(funkcja_b, funkcja_b_pochodna);
    sieczne(funkcja_b);

    return 0;
}


