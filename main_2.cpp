#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

#define FIELD_SIZE 20

const int MAX_ITERATIONS = 5;
const double EPSILON = 2.2e-16;

double function(double x) {
    return (1.0 - exp(-x)) / x; 
}

double function_tylor(double x) {
    double sum = 1.0, prev = 1.0;
    double i = 1.0;
    while(i < MAX_ITERATIONS && (std::abs(prev) > EPSILON) ) {
        prev *= -x / (1.0 + i);
        sum += prev; // na przemian odejmujmy i dodajemy  
        i += 1.0;
    }
    return sum;
}

double blad_wzgledny(double expected, double result) {
    return abs((result - expected) / expected);
}

void process_file() {
    std::fstream stream("data/oneminexp_ref.txt");
    double _tmp, x, expected;
    while (stream.good()) {
        stream >> _tmp;
        stream >> x;
        stream >> expected;

        double result; 
        if(x < 0.2) {
            result = function_tylor(x);
        } else {
            result = function(x);
        }

        // std::cout.width(FIELD_SIZE);
        std::cout << std::internal << x << ",";

        // std::cout.width(FIELD_SIZE);
        std::cout << std::internal << result << ",";

        // std::cout.width(FIELD_SIZE);
        std::cout << std::internal << blad_wzgledny(expected, result) << std::endl;
    }
}

int main() {
    // HEADER
    std::cout.precision(10);

    // std::cout.width(FIELD_SIZE);
    std::cout << std::internal << "X,";

    // std::cout.width(FIELD_SIZE);
    std::cout << std::internal << "Wynik_przyblizony,";

    // std::cout.width(FIELD_SIZE);
    std::cout << std::internal << "Blad_wzgledny" << std::endl;    

    // RESULT
    process_file();
    return 0;
}