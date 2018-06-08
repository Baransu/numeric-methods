#include <iostream>
#include <cassert>
#include <cmath>

int find_mantis_size_float(float &mantis) {
    const float TWO = 2.0f;
    const float ONE = 1.0f;
    int i = 0;
    float to_epsilon = ONE, test, prev;

    do {
        prev = to_epsilon;
        to_epsilon = to_epsilon / TWO;
        test = to_epsilon + ONE;
        // std::cout << to_epsilon << std::endl;
    } while (test > ONE && ++i);

    mantis = prev;
    return i;
}

int find_mantis_size_double(double &mantis) {
    const double TWO = 2.0;
    const double ONE = 1.0;
    int i = 0;
    double to_epsilon = ONE, test, prev;
    
    do {
        prev = to_epsilon;
        to_epsilon = to_epsilon / TWO;
        test = to_epsilon + ONE;
        // std::cout << to_epsilon << std::endl;
    } while (test > ONE && ++i);

    mantis = prev;
    return i;
}

int main() {
    float float_epsilon;
    int float_mantis = find_mantis_size_float(float_epsilon);
    std::cout << "Mantysa float: " << float_mantis << std::endl;
    std::cout << "Epsilon maszynowy float: " << float_epsilon << std::endl;
    assert(float_mantis == 23);

    double double_epsilon;
    int double_mantis = find_mantis_size_double(double_epsilon);
    std::cout << "Mantysa double: " << double_mantis << std::endl;
    std::cout << "Epsilon maszynowy double: " << double_epsilon << std::endl;
    assert(double_mantis == 52);

    return 0;
}

/*

Dzieląc 1 przez 2 dazymy do najmniejszej liczby f(epsilon + 1) > 1.
Osiagajac ja, ilość iteracji odpowiada ilości bitów mantysy

Precyzja arytmetyki
    v = 2^(t+1)
    epsilon = 2 * v = 2^(-t)

Typ     |  t  | Precyzja
------------------------
float   | 23  | 6*10^-8
double  | 52  | 10^-16

*/