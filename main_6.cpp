#include <iostream>
#include <cmath>

const int SIZE = 6;

/*
 * u - diagonala górna
 * d - główna
 * l - dolna
 *
 * Przykład:
 *
 * d u 0 0 0
 * l d u 0 0
 * 0 l d u 0
 * 0 0 l d u
 * 0 0 0 l d
 */

void fill_diagonals(double *u, double *d, double *l) {
    // gorna
    u[0] = 2.0 / 3.0; u[1] = 5.0 / 6.0; u[2] = 9.0 / 10.0; u[3] = 13.0 / 14.0; u[4] = 17.0 / 18.0;

    // glowna
    d[0] = 30.0;  d[1] = 20.0;   d[2] = 10.0;  d[3] = 10.0;  d[4] = 20.0;  d[5] = 30.0;

    // dolna
    l[0] = 3.0 / 4.0; l[1] = 7.0 / 8.0; l[2] = 11.0 / 12.0; l[3] = 15.0 / 16.0; l[4] = 19.0 / 20.0; 
}

double * gen_vector_b() {
    double * b = new double[SIZE];
    b[0] = 94.0 / 3.0;
    b[1] = 173.0 / 4.0;
    b[2] = 581.0 / 20.0;
    b[3] = -815.0 / 28.0;
    b[4] = -6301.0 / 144.0;
    b[5] = -319.0 / 10.0;
    return b;
}

double* thomas(double *upper, double * diagonal, double * lower, int n) {
    double * eta = new double[n];
    eta[0] = diagonal[0];

    // eta_2 = d_2 = l_2/eta_1 * u_2
    for (int i = 1; i < n; ++i) {
        eta[i] = diagonal[i] - lower[i - 1] / eta[i - 1] * upper[i - 1];
    }

    return eta;
}

double * solve(double * eta, double * b, double * upper, double * lower, int n) {
    // Wyznaczanie wektora r
    double * r = new double[n];
    r[0] = b[0];

    for (int i = 1; i < n; ++i) {
        r[i] = b[i] - lower[i - 1] / eta[i - 1] * r[i - 1];
    }

    // Wyznaczanie rozwiązania
    double * x = new double[n];
    x[n - 1] = r[n - 1] / eta[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        x[i] = (r[i] - upper[i] * x[i + 1]) / eta[i];
    }
    delete[] r;

    return x;
}

void print_vector(double *v, int m) {
    for (int j = 0; j < m; j++) {
        std::cout.precision(4);
        std::cout << "\t" << v[j];
    }
    printf("\n");
}

int main() {

    // Inicjalizacja macierzy troj-diagonalnej
    double * u = new double[SIZE - 1];
    double * d = new double[SIZE];
    double * l = new double[SIZE - 1];
    fill_diagonals(u, d, l);

    // Inicjalizacja wektora b
    double * b = gen_vector_b();

    // Dane początkowe
    printf("Dane:\n\n");

    printf("u:\n");
    print_vector(u, SIZE - 1);

    printf("d:\n");
    print_vector(d, SIZE);

    printf("l:\n");
    print_vector(l, SIZE - 1);

    printf("b:\n");
    print_vector(b, SIZE);

    double * eta = thomas(u, d, l, SIZE);

    // Rozwiązanie układu
    double * x = solve(eta, b, u, l, SIZE);

    // Wypisanie wyniku
    printf("Rozwiazanie:\n");
    print_vector(x, SIZE);

    // Czyszczenie pamięci
    delete[] l, d, u, b, x, eta;

    return 0;
}