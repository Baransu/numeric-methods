#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

#define PI 3.14159265358979323846
#define STEP 0.1
#define STEP_COUNT 20
#define METHOD_COUNT 5

template<typename T> void zapis_danych(T *kroki, T **wyniki);

template<typename T> T fun(T x) {
    return cos(x / 2);
}

template<typename T> T roznica_progresywna(T x, T h) {
    return (fun(x + h) - fun(x)) / h;
}

template<typename T> T roznica_wsteczna(T x, T h) {
    return (fun(x) - fun(x - h)) / h;
}

template<typename T> T roznica_centralna(T x, T h) {
    return (fun(x + h) - fun(x - h)) / (2.0 * h);
}

template<typename T> T roznica_progresywna_trzypunktowa(T x, T h) {
    return (4.0 * fun(x + h) - (3.0 * fun(x) + fun(x + 2.0 * h))) / (2.0 * h);
}

template<typename T> T roznica_wsteczna_trzypunktowa(T x, T h) {
    return (fun(x - 2.0 * h) - 4.0 * fun(x - h) + 3.0 * fun(x)) / (2.0 * h);
}

template<typename T> T pochodna(T x) {
    return (-0.5 * sin(x / 2.0));
}

template<typename T> void oblicz_roznice(T *kroki, T **wyniki) {
    T poczatek = 0.0;
    T koniec = PI; // pi
    T srodek = (koniec - poczatek) / 2;
    T krok = STEP;
    for (int i = 0; i < STEP_COUNT; i++) {
        kroki[i] = krok;

        wyniki[0][i] = fabs(pochodna(srodek) - roznica_wsteczna(srodek, krok));
        wyniki[1][i] = fabs(pochodna(srodek) - roznica_centralna(srodek, krok));
        wyniki[2][i] = fabs(pochodna(srodek) - roznica_progresywna(srodek, krok));
        wyniki[3][i] = fabs(pochodna(koniec) - roznica_wsteczna(koniec, krok));
        wyniki[4][i] = fabs(pochodna(koniec) - roznica_wsteczna_trzypunktowa(koniec, krok));
        krok /= 10;
    }
}

int main() {

    float *krokiFloat, **wynikiFloat;
    double *krokiDouble, **wynikiDouble;
  

    krokiFloat = new float[STEP_COUNT];
    krokiDouble = new double[STEP_COUNT];
    wynikiFloat = new float *[METHOD_COUNT];
    wynikiDouble = new double *[METHOD_COUNT];

    for (int i = 0; i < METHOD_COUNT; i++) {
        wynikiFloat[i] = new float[STEP_COUNT];
        wynikiDouble[i] = new double[STEP_COUNT];
    }

    oblicz_roznice(krokiFloat, wynikiFloat);
    oblicz_roznice(krokiDouble, wynikiDouble);
    
    zapis_danych(krokiFloat, wynikiFloat);
    zapis_danych(krokiDouble, wynikiDouble);

    system("gnuplot data/wykres_8.plt");

    return 0;
}

template<typename T> void zapis_danych(T *kroki, T **wyniki) {
    string *opisy;
    opisy = new string[METHOD_COUNT + 1];
    opisy[0] = "Krok";
    opisy[1] = "center wst2";
    opisy[2] = "center centr";
    opisy[3] = "center prog2";
    opisy[4] = "end wst2";
    opisy[5] = "end wst3";

    fstream plik;
    string nazwa = "data/data_";
    nazwa += typeid(T).name();
    nazwa += ".txt";
    plik.open(nazwa.c_str(), fstream::out);
    plik << left << "#";
    plik.width(6);
    plik << left << opisy[0];

    for (int i = 1; i < METHOD_COUNT + 1; i++) {
        plik.width(13);
        plik << left << opisy[i];
    }

    plik << endl;
    for (int i = 0; i < STEP_COUNT; i++) {
        plik.width(5);
        plik << left << log10(kroki[i]) << " ";
        for (int j = 0; j < METHOD_COUNT; j++) {
            plik.width(12);
            plik << left << log10(wyniki[j][i]) << " ";
        }
        plik << endl;
    }
    plik << endl << endl;
    plik.close();
}
