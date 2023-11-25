#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <filesystem>
#include "Tekran.h"
#include "TBaza_Hasel.h"

using namespace std;

void opening_existing_db(int* menu_option, Tekran* screen, vector<TBaza_Hasel>* SYLABUS);
void creating_new_db(int* menu_option, Tekran* screen, vector<TBaza_Hasel>* databases);
void quit_program(int* SYLABUS1, Tekran* SYLABUS2, vector<TBaza_Hasel>* SYLABUS3);

int main() {
    Tekran screen;
    vector<TBaza_Hasel> databases;
    screen.switch_view(0);
    void (*menu[3])(int*, Tekran*, vector<TBaza_Hasel>*) = {&opening_existing_db, &creating_new_db, &quit_program};
    int menu_option = 1;

    while (true) {
        int c = getch();
        if (c == 13) {
            switch (menu_option) {
                case 1:
                    menu[0](&menu_option, &screen, nullptr);
                    break;
                case 2:
                    menu[1](&menu_option, &screen, &databases);
                    break;
                case 3:
                    menu[2](nullptr, nullptr, nullptr);
                    break;
            }
        }
        switch (c) {
            case 80:
                if (menu_option < 3) {
                    screen.ekran[menu_option].erase(0, 3);
                    screen.ekran[menu_option].insert(0, " ");
                    menu_option++;
                    screen.ekran[menu_option].erase(0, 1);
                    screen.ekran[menu_option].insert(0, u8"→");
                    screen.render(screen.ekran_size);
                }
                break;
            case 72:
                if (menu_option > 1) {
                    screen.ekran[menu_option].erase(0, 3);
                    screen.ekran[menu_option].insert(0, " ");
                    menu_option--;
                    screen.ekran[menu_option].erase(0, 1);
                    screen.ekran[menu_option].insert(0, u8"→");
                    screen.render(screen.ekran_size);
                }
                break;
        }
    }
}

void opening_existing_db(int* menu_option, Tekran* screen, vector<TBaza_Hasel>* SYLABUS) {
    if (*menu_option == 1) {
        vector<string> file_list;
        for (const auto&entry: std::filesystem::directory_iterator("./"))
            if (entry.path().extension() == ".mudhut") {
                string path = entry.path().u8string().erase(0, 2);
                file_list.push_back(path);
            }
        if (file_list.size()) {
            screen->views[2].erase(screen->views[2].begin() + 1, screen->views[2].end());
            for (int i = 0; i < file_list.size(); ++i) {
                if (i == 0) {
                    screen->views[2].push_back("→ " + file_list[i]);
                    continue;
                }
                screen->views[2].push_back("  " + file_list[i]);
            }
            screen->switch_view(2);
            int c;
            unsigned long long wybor_menu = 1;
            while ((c = getch()) != 13 && c != 27) {
                switch (c) {
                    case 80:
                        if (wybor_menu < file_list.size()) {
                            screen->ekran[wybor_menu].erase(0, 3);
                            screen->ekran[wybor_menu].insert(0, " ");
                            wybor_menu++;
                            screen->ekran[wybor_menu].erase(0, 1);
                            screen->ekran[wybor_menu].insert(0, u8"→");
                            screen->render(screen->ekran_size);
                        }
                        break;
                    case 72:
                        if (wybor_menu > 1) {
                            screen->ekran[wybor_menu].erase(0, 3);
                            screen->ekran[wybor_menu].insert(0, " ");
                            wybor_menu--;
                            screen->ekran[wybor_menu].erase(0, 1);
                            screen->ekran[wybor_menu].insert(0, u8"→");
                            screen->render(screen->ekran_size);
                        }
                        break;
                }
            }
            if (c == 13) {
                TBaza_Hasel db{file_list[wybor_menu - 1]};
                db.display_data_base();
            }
            screen->switch_view(0);
        }
        else {
            screen->views[2].push_back("Brak elementów w bazie so far :/");
            screen->switch_view(2);
        }
        *menu_option = 1;
    }
}

void creating_new_db(int* menu_option, Tekran* screen, vector<TBaza_Hasel>* databases) {
    screen->switch_view(1);
    databases->push_back(TBaza_Hasel{});
    screen->switch_view(0);
    *menu_option = 1;
}

void quit_program(int* SYLABUS1, Tekran* SYLABUS2, vector<TBaza_Hasel>* SYLABUS3) {
    exit(0);
}
