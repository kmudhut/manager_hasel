#pragma once
#include <iostream>
#include <vector>

struct Tekran {
    static constexpr int width = 75;
    int ekran_size = 0;
    std::vector<std::string> views[3]
    {
        {
            std::string((width - std::string(u8"MANAGER HASEŁ").size()) / 2, '=') + u8" MANAGER HASEŁ " + std::string(
                (width - std::string(u8"MANAGER HASEŁ").size()) / 2, '='),
            u8"→ Otwórz istniejącą bazę", u8"  Utwórz nową bazę", u8"  Zakończ program"
        },
        {
            std::string((width - std::string(u8"MANAGER HASEŁ (tworzenie nowej bazy)").size()) / 2, '=') +
            u8" MANAGER HASEŁ (tworzenie nowej bazy) " + std::string(
                (width - std::string(u8"MANAGER HASEŁ (tworzenie nowej bazy)").size()) / 2, '=')
        },
        {
            std::string((width - std::string(u8"MANAGER HASEŁ (lista zapisanych baz)").size()) / 2, '=') +
            u8" MANAGER HASEŁ (lista zapisanych baz) " + std::string(
                (width - std::string(u8"MANAGER HASEŁ (lista zapisanych baz)").size()) / 2, '=')
        }
    };
    std::string* ekran = nullptr;
    void render(int ekran_size) const;
    void switch_view(int view);
     ~Tekran() {
        delete [] ekran;
    }

};
