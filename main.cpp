#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

struct Tekran {
    static constexpr int width = 75;
    int ekran_size = 0;
    vector<string> views[3] =
    {
        {
            string((width - string(u8"MANAGER HASEŁ").size()) / 2, '=') + u8" MANAGER HASEŁ " + string(
                (width - string(u8"MANAGER HASEŁ").size()) / 2, '='),
            u8"→ Otwórz istniejącą bazę", u8"  Utwórz nową bazę", u8"  Zakończ program"
        },
        {
            string((width - string(u8"MANAGER HASEŁ (tworzenie nowej bazy)").size()) / 2, '=') +
            u8" MANAGER HASEŁ (tworzenie nowej bazy) " + string(
                (width - string(u8"MANAGER HASEŁ (tworzenie nowej bazy)").size()) / 2, '=')
        }
    };
    string* ekran = nullptr;


    void render(int ekran_size) {
        system("chcp 65001");
        system("cls");
        for (int i = 0; i < ekran_size; i++) {
            cout << *(ekran + i) << endl;
        }
    }

    void switch_view(int view) {
        ekran_size = views[view].size();
        delete [] ekran;
        ekran = new string [ekran_size];
        for (int i = 0; i < ekran_size; i++) {
            ekran[i] = views[view][i];
        }
        render(ekran_size);
    }

    ~Tekran() {
        delete [] ekran;
    }
};

struct TBaza_Hasel {
    string name;
    string password;
    vector<vector<string>> data;

    TBaza_Hasel() {
        cout << "Podaj nazwę nowej bazy haseł:";
        string new_database_name;
        cin >> new_database_name;
        name = new_database_name;
        cout << "Utwórz hasło nowej bazy:";
        string new_database_password;
        int c;
        while ((c = getch()) != 13) {
            putch('*');
            new_database_password.push_back(c);
        }
        password = new_database_password;
        cin.get();
        int i = 0;
        do {
            vector<string> tmp(3);
            cout << endl << "\tNazwa wpisu:";
            getline(cin, tmp[0]);

            cout << "\tLogin:";
            getline(cin, tmp[1]);
            cout << "\tCzy chcesz wprowadzić hasło ręcznie? [t/n]:";
            char c;
            while ((c = getch()) != 't' && (c != 'n'));

            if (c == 't') {
                cout << endl << "\tHasło:";
                getline(cin, tmp[2]);
            }
            else if (c == 'n') {
                cout << endl << "\t\tPodaj parametry generowanego hasła:\n";
                cout << "\t\tDługość hasła:";
                int length;
                cin >> length;

                cout << "\t\tDuże litery? [t/n]:";
                while ((c = getch()) != 't' && (c != 'n'));
                bool upper_case = (c == 't' ? true : false);

                cout << endl << "\t\tMałe litery? [t/n]:";
                while ((c = getch()) != 't' && c != 'n');
                bool lower_case = (c == 't' ? true : false);

                cout << endl << "\t\tCyfry? [t/n]:";

                while ((c = getch()) != 't' && c != 'n');
                bool digits = (c == 't' ? true : false);

                cout << endl << "\t\tZnaki specjalne? [t/n]:";
                while ((c = getch()) != 't' && c != 'n');
                bool special_characters = ((c == 't')?true : false);

                cout << "\n\tHasło:" << (tmp[2] = generate_password(length, upper_case, lower_case, digits, special_characters));
            }


            data.push_back(tmp);

            cout << endl <<
                    "Wpis został dodany do bazy haseł. Zakończ wprowadzanie - ESC, kontynuuj - dowolny przycisk.";
        }
        while (getch() != 27);
        export_data_base_to_file();
    };

    TBaza_Hasel(string filename) {
        import_data_base_from_file(filename);
    }

    string encrypt_line(string line) const {
        string encrypted_line;
        for (int i = 0, j = 0; i < line.size(); ++i) {
            if (i % 2 == 0) {
                encrypted_line.push_back(line.at(i) + 1);
                string random;
                for (int i = 0; i < 10; i++) {
                    random.push_back(rand() % 127 + 65);
                }
                encrypted_line.insert(encrypted_line.length(), random);
            }
            else encrypted_line.push_back(line.at(i) - 1);
        }
        return encrypted_line;
    }

    string decrypt_line(string line) const {
        string decrypted_line;
        for (int i = 0; i < line.size(); ++i) {
            if (i % 2 == 0) {
                decrypted_line.push_back(line.at(i) - 1);
                i += 10;
            }
            else decrypted_line.push_back(line.at(i) + 1);
        }
        return decrypted_line;
    }

    static string generate_password(int length, bool upper_case, bool lower_case, bool digits, bool special_characters) {
        vector<char> charset;
        string generated_password;
        if (upper_case) {
            for (char i = 65; i <= 90; i++) {
                charset.push_back(i);
            }
        }
        if (lower_case) {
            for (char i = 97; i <= 122; i++) {
                charset.push_back(i);
            }
        }
        if (digits) {
            for (char i = 48; i <= 57; i++) {
                charset.push_back(i);
            }
        }
        if (special_characters) {
            for (char i = 33; i <= 47; i++) {
                charset.push_back(i);
            }
            for (char i = 58; i <= 64; i++) {
                charset.push_back(i);
            }
        }

        for(int i = 0; i<length; ++i) {
            random_device rd;
            mt19937 mt(rd());
            uniform_int_distribution<int> random(0, charset.size()-1);
            generated_password.push_back(charset.at(random(mt)));
        }

        return generated_password;
    }

    void export_data_base_to_file() const {
        ofstream plik;
        plik.open(name + ".mudhut");
        plik << encrypt_line(name) << endl;
        plik << encrypt_line(password);
        plik.close();
    }

    void import_data_base_from_file(string filename) {
        ifstream plik;
        plik.open(filename);
        string tmp;
        getline(plik, tmp);
        name = decrypt_line(tmp);
        getline(plik, tmp);
        password = decrypt_line(tmp);
    }
};

int main() {
    //TBaza_Hasel A =TBaza_Hasel("sluzbowa.mudhut");
    // cout<<A.password;
    // cin.get();

    srand(time(nullptr));
    Tekran e;
    vector<TBaza_Hasel> databases;
    e.switch_view(0);
    int wybor_menu = 1;

    while (true) {
        int c = getch();
        if (c == 13) {
            if (wybor_menu == 3) exit(0);
            e.switch_view(1);
            databases.push_back(TBaza_Hasel{});
            e.switch_view(0);
        }
        switch (c) {
            case 80:
                if (wybor_menu < 3) {
                    e.ekran[wybor_menu].erase(0, 3);
                    e.ekran[wybor_menu].insert(0, " ");
                    wybor_menu++;
                    e.ekran[wybor_menu].erase(0, 1);
                    e.ekran[wybor_menu].insert(0, u8"→");
                    e.render(e.ekran_size);
                }
                break;
            case 72:
                if (wybor_menu > 1) {
                    e.ekran[wybor_menu].erase(0, 3);
                    e.ekran[wybor_menu].insert(0, " ");
                    wybor_menu--;
                    e.ekran[wybor_menu].erase(0, 1);
                    e.ekran[wybor_menu].insert(0, u8"→");
                    e.render(e.ekran_size);
                }
                break;
        }
    }
    cin.get();
    cin.get();
}
