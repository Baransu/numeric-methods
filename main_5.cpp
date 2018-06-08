#include <iostream>
#include <cmath>

#define MATRIX_SIZE 4

using namespace std;

double **get_matrix() {
    double **A = new double *[MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; ++i) {
        A[i] = new double[MATRIX_SIZE];

    }
    A[0][0] = 1.0;
    A[0][1] = 20.0;
    A[0][2] = -30.0;
    A[0][3] = -4.0;
    A[1][0] = 4.0;
    A[1][1] = 20.0;
    A[1][2] = -6.0;
    A[1][3] = 50.0;
    A[2][0] = 9.0;
    A[2][1] = -18.0;
    A[2][2] = 12.0;
    A[2][3] = -11.0;
    A[3][0] = 16.0;
    A[3][1] = -15.0;
    A[3][2] = 14.0;
    A[3][3] = 130.0;

    return A;
}

double **copy(double **M, int m, int n) {
    double **C = new double *[m];
    for (int i = 0; i < m; i++) {
        C[i] = new double[n];
        for (int j = 0; j < n; j++) {
            C[i][j] = M[i][j];
        }
    }
    return C;
}

double **empty_matrix(int m, int n) {
    double **M = new double *[m];
    for (int i = 0; i < m; i++) {
        M[i] = new double[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = 0;
        }
    }
    return M;
}

double *get_vector() {
    double *b = new double[MATRIX_SIZE];
    b[0] = 0.0;
    b[1] = 114.0;
    b[2] = -5.0;
    b[3] = 177.0;
    return b;
}

void print_matrix(double **A, int size, int *indices) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout.precision(4);
            cout << "\t" << A[indices[i]][j];
        }
        printf("\n");
    }
}

void print_vector(double *v, int size, int *indices) {
    for (int j = 0; j < size; j++) {
        cout.precision(4);
        cout << "\t" << v[indices[j]];
    }
    printf("\n");
}

// lista 
int *get_indexex_list(int size) {
    int *indices = new int[size];
    for (int i = 0; i < size; i++) {
        indices[i] = i;
    }
    return indices;
}

// wybór elementu podstawowego
void partial_pivot(double **A, int k, int size, int *indices) {
    int row = 0;
    for (int i = k + 1; i < size - 1; i++) {
        if (fabs(A[indices[i]][k]) < fabs(A[indices[i + 1]][k])) {
            row = i + 1;
        }
    }

    int t = indices[row];
    indices[row] = indices[k];
    indices[k] = t;
}

void decomposeLU(double **A, double **L, double **U, int size, int *indices) {
    L[indices[0]][0] = 1;
    for (int k = 0; k < size - 1; k++) {
        if (U[indices[k]][k] == 0.0) {
            partial_pivot(U, k, size, indices);
        }
        for (int i = k + 1; i < size; i++) {
            double factor = U[indices[i]][k] / U[indices[k]][k];
            for (int j = k; j < size; j++) {
                U[indices[i]][j] -= U[indices[k]][j] * factor;
                if (j < i) {
                    L[indices[i]][j] = factor;
                }
            }
        }
        L[indices[k + 1]][k + 1] = 1;
    }
}

double* solution(double **L, double **U, double *b, int *it, int n) {
    double *x = new double[MATRIX_SIZE];
    double *y = new double[MATRIX_SIZE];
    for (int i = 0; i < n; i++) {
        y[i] = b[i];
    }
    for (int k = 0; k < n - 1; k++) {
        for (int i = k + 1; i < n; i++) {
            y[it[i]] -= y[it[k]] * L[it[i]][k];
        }
    }
    x[it[n - 1]] = y[it[n - 1]] / U[it[n - 1]][n - 1];
    for (int i = n - 2; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += U[it[i]][j] * x[it[j]];
        }
        x[it[i]] = (y[it[i]] - sum) / U[it[i]][i];
    }
    delete[] y;
    return x;
}

int main() {
    double **A = get_matrix();
    double **L = empty_matrix(MATRIX_SIZE, MATRIX_SIZE);
    double **U = copy(A, MATRIX_SIZE, MATRIX_SIZE);
    double *b = get_vector();
    int *index_table = get_indexex_list(MATRIX_SIZE);

    printf("\nDane:\n");
    printf("\nMacierz A:\n");
    print_matrix(A, MATRIX_SIZE, index_table);
    printf("\nWektor b:\n");
    print_vector(b, MATRIX_SIZE, index_table);

    // Dekompozycja LU
    decomposeLU(A, L, U, MATRIX_SIZE, index_table);

    // Rozwiązanie układu
    double *x = solution(L, U, b, index_table, MATRIX_SIZE);

    printf("\nRozwiazanie:\n\n");

    printf("\nL:\n");
    print_matrix(L, MATRIX_SIZE, index_table);
    printf("\nU:\n");
    print_matrix(U, MATRIX_SIZE, index_table);

    printf("\nx:\n");
    print_vector(x, MATRIX_SIZE, index_table);

    // czysczenie pamieci
    for (int i = 0; i < MATRIX_SIZE; i++) {
        delete[] A[i], L[i], U[i];
    }   

    delete[] A, L, U, b, x, index_table;
    return 0;
}