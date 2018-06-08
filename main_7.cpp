#include <iostream>
#include <iomanip>
#include <cmath>

#define ROW_SEPARATOR ' '
#define NAME_WIDTH 20
#define DATA_WIDTH 20
#define SIZE 4
#define MAX_ITERATION_COUNT 100
#define MAX_ERROR 10e-6
#define PRECISION 10e-7
#define OMEGA 1 // 0 < OMEGA < 2

//  https://stackoverflow.com/questions/14765155/how-can-i-easily-format-my-data-table-in-c

void print_vector(double *x) {
    for (int i = 0; i < SIZE; i++) {
        std::cout << std::left << std::setw(DATA_WIDTH) << std::setfill(ROW_SEPARATOR) << x[i];
    }
}

void write_start_b(double *b) {
    b[0] = 395.0;
    b[1] = 603.0;
    b[2] = -415.0;
    b[3] = -606.0;
}

void write_start_values(double *x) {
    x[0] = 1.0;
    x[1] = 1.0;
    x[2] = 1.0;
    x[3] = 1.0;
}

void write_start_a(double **A) {
    A[0][0] = 100.0;  A[0][1] = 1.0;    A[0][2] = -2.0;    A[0][3] = 3.0;
   
    A[1][0] = 4.0;    A[1][1] = 300.0;  A[1][2] = -5.0;    A[1][3] = 6.0;
    
    A[2][0] = 7.0;    A[2][1] = -8.0;   A[2][2] = 400.0;   A[2][3] = 9.0;
  
    A[3][0] = -10.0;  A[3][1] = 11.0;   A[3][2] = -12.0;   A[3][3] = 200.0;
   }


double estimator(double *x_old, double *x) {
    double temp[4];
    temp[0] = fabs(x[0] - x_old[0]);
    temp[1] = fabs(x[1] - x_old[1]);
    temp[2] = fabs(x[2] - x_old[2]);
    temp[3] = fabs(x[3] - x_old[3]);

    return *(std::max_element(temp, temp + 4));
}

// norma maximum ||b-Ax||
double residuum(double **A, double *b, double *x) {
    double residuum_vector_temp[4];

    residuum_vector_temp[0] = fabs((A[0][0] * x[0] + A[0][1] * x[1] + A[0][2] * x[2] + A[0][3] * x[3]) - b[0]);
    residuum_vector_temp[1] = fabs((A[1][0] * x[0] + A[1][1] * x[1] + A[1][2] * x[2] + A[1][3] * x[3]) - b[1]);
    residuum_vector_temp[2] = fabs((A[2][0] * x[0] + A[2][1] * x[1] + A[2][2] * x[2] + A[2][3] * x[3]) - b[2]);
    residuum_vector_temp[3] = fabs((A[3][0] * x[0] + A[3][1] * x[1] + A[3][2] * x[2] + A[3][3] * x[3]) - b[3]);

    return *(std::max_element(residuum_vector_temp, residuum_vector_temp + 4));
}

void print_table_header() {
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "x1";
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "x2";
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "x3";
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "x4";
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "Estymator błedu";
    std::cout << std::left << std::setw(NAME_WIDTH) << std::setfill(ROW_SEPARATOR) << "Residuum";
    std::cout << std::endl << std::endl;
    std::cout.precision(10);
}

void print_table_row(double **A, double *x_old, double *x, double *b) {
    print_vector(x);
    std::cout << std::left << std::setw(DATA_WIDTH) << std::setfill(ROW_SEPARATOR) << estimator(x_old, x);
    std::cout << std::left << std::setw(DATA_WIDTH) << std::setfill(ROW_SEPARATOR) << residuum(A, b, x) << std::endl;
}

void solve_jacoby(double **A, double *x_old, double *x, double *b) {
    double sum = 0.0;
    int iteration_counter = 0;
    print_table_header();
    do {
        for (int i = 0; i < SIZE; i++) {
            sum = 0.0;
            for (int j = 0; j < SIZE; j++) {
                if (j != i) {
                   sum += A[i][j] * x_old[j];
                } 
            }
            x_old[i] = x[i];
            x[i] = (b[i] - sum) / A[i][i];
        }
        print_table_row(A, x_old, x, b);  
    } while (iteration_counter++ < MAX_ITERATION_COUNT && estimator(x_old, x) > MAX_ERROR && residuum(A, b, x) > PRECISION);

    // Arbitralne ilość iteracji
    // Kryterium dokładności wyznaczenia xn
    // Kryterium wiarygodności xn jako przybliżenie pierwiastka
}

void solve_gaussa_seidel(double **A, double *x_old, double *x, double *b) {
    double sum = 0.0;
    int iteration_counter = 0;
    print_table_header();
    do {
        for (int i = 0; i < SIZE; ++i) {
            sum = 0.0;
            for (int j = 0; j < i; ++j) {
                sum += (A[i][j] * x[j]);
            }

            for (int j = i + 1; j < SIZE; ++j) {
                sum += (A[i][j] * x[j]);
            }

            x_old[i] = x[i];
            x[i] = (b[i] - sum) / A[i][i];
        }
        print_table_row(A, x_old, x, b);    
    } while (iteration_counter++ < MAX_ITERATION_COUNT && estimator(x_old, x) > MAX_ERROR && residuum(A, b, x) > PRECISION);     
}

void solve_sor(double **A, double *x_old, double *x, double *b, double omega) {
    double sum = 0.0;
    int iteration_counter = 0;
    print_table_header();
    do {
        for (int i = 0; i < SIZE; i++) {
            sum = 0.0;
            for (int j = 0; j < SIZE; j++) {
                if (j != i) sum += A[i][j] * x[j];
            }
            x_old[i] = x[i];
            x[i] = (1.0 - omega) * x[i] + (omega / A[i][i]) * (b[i] - sum);
        }
        print_table_row(A, x_old, x, b);
    } while (iteration_counter++ < MAX_ITERATION_COUNT && estimator(x_old, x) > MAX_ERROR && residuum(A, b, x) > PRECISION);
}


int main() {
    double **A;
    double *b = new double[SIZE];
    double *x_old = new double[SIZE];
    double *x = new double[SIZE];

    A = new double *[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        A[i] = new double[SIZE];
    }

    write_start_a(A);
    write_start_b(b);

    // JACOBY
    write_start_values(x_old);
    write_start_values(x);
    printf("\n\nMetoda Jacobiego:\n\n");
    solve_jacoby(A, x_old, x, b);

    // GAUSS-SEIDEL
    write_start_values(x_old);
    write_start_values(x);
    printf("\n\nMetoda Gaussa-Seidela:\n\n");
    solve_gaussa_seidel(A, x_old, x, b);

    // SOR
    write_start_values(x_old);
    write_start_values(x);
    printf("\n\nMetoda SOR:\n\n");
    solve_sor(A, x_old, x, b, OMEGA);

    for (int i = 0; i < SIZE; i++) {
        delete[] A[i];
    }

    delete[] A;
    delete[] b;

    return 0;
}