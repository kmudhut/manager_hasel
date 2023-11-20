#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>

using namespace std;

struct Tekran {
    static constexpr int width = 75;

    string ekran[width]{
        string((width - string(u8"MANAGER HASEŁ").size()) / 2, '=') + u8" MANAGER HASEŁ " + string(
            (width - string(u8"MANAGER HASEŁ").size()) / 2, '='),
        u8"→ Otwórz istniejącą bazę", u8"  Utwórz nową bazę", u8"  Zakończ program"
    };


    void render(/*string *tab, int size = width*/) {
        system("chcp 65001");
        system("cls");
        for (int i = 0; i < 4; i++) {
            cout << *(ekran + i) << endl;
        }
    }
};

int main() {
    Tekran e;
    e.render();
    int wybor_menu = 1;

    while (true) {
        int a;
        int c;
        getch();
        switch (c = getch()) {
            case 80:
                if (wybor_menu < 3) {
                    e.ekran[wybor_menu].erase(0, 3);
                    e.ekran[wybor_menu].insert(0, " ");
                    wybor_menu++;
                    e.ekran[wybor_menu].erase(0, 1);
                    e.ekran[wybor_menu].insert(0, u8"→");
                    e.render();
                }
                break;
            case 72:
                if (wybor_menu > 1) {
                    e.ekran[wybor_menu].erase(0, 3);
                    e.ekran[wybor_menu].insert(0, " ");
                    wybor_menu--;
                    e.ekran[wybor_menu].erase(0, 1);
                    e.ekran[wybor_menu].insert(0, u8"→");
                    e.render();
                }
        }
    }
    cin.get();
    cin.get();
}
