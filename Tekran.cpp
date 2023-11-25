#include "Tekran.h"
#include <iostream>
using namespace std;

void Tekran::render(int ekran_size) const {
    system("chcp 65001");
    system("cls");
    for (int i = 0; i < ekran_size; i++) {
        cout << *(ekran + i) << endl;
    }
}

void Tekran::switch_view(int view) {
    ekran_size = views[view].size();
    delete [] ekran;
    ekran = new string [ekran_size];
    for (int i = 0; i < ekran_size; i++) {
        ekran[i] = views[view][i];
    }
    render(ekran_size);
}