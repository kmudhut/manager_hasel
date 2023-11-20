#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

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
            string((width - string(u8"MANAGER HASEŁ (tworzenie nowej bazy)").size()) / 2, '=') + u8" MANAGER HASEŁ (tworzenie nowej bazy) " + string(
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
        ekran = new string [ekran_size];
        for(int i = 0; i<ekran_size; i++) {
            ekran[i] = views[view][i];
        }
        render(ekran_size);
    }
};

struct TBaza_Hasel {
    string name;
    string password;
    vector<vector<string>> data;

    TBaza_Hasel() {
        cout<<"Podaj nazwę nowej bazy haseł:";
        string new_database_name;
        cin>>new_database_name;
        name = new_database_name;
        cout<<"Utwórz hasło nowej bazy:";
        string new_database_password;
        int c;
        while((c = getch()) != 13){
            putch('*');
            new_database_password.push_back(c);
        }
        password = new_database_password;
        export_data_base_to_file();
    };

    TBaza_Hasel(string filename) {
        import_data_base_from_file(filename);
    }

    string encrypt_line(string line) const {
        string encrypted_line;
        for(int i = 0, j=0; i<line.size(); ++i) {
            if(i%2==0) {
                encrypted_line.push_back(line.at(i)+1);
                string random;
                for(int i = 0; i<10; i++) {
                    random.push_back(rand()%127+65);
                }
                encrypted_line.insert(encrypted_line.length(),random);
            }
            else encrypted_line.push_back(line.at(i)-1);
        }
        return encrypted_line;
    }

    string decrypt_line(string line) const {
        string decrypted_line;
        for(int i = 0; i<line.size(); ++i) {
            if(i%2==0) {
                decrypted_line.push_back(line.at(i)-1);
                i+=10;
            }
            else decrypted_line.push_back(line.at(i)+1);
        }
        return decrypted_line;
    }

    void export_data_base_to_file() const {
        ofstream plik;
        plik.open(name + ".mudhut");
        plik<<encrypt_line(name)<<endl;
        plik<<encrypt_line(password);
        plik.close();
    }

    void import_data_base_from_file(string filename) {
        ifstream plik;
        plik.open(filename);
        string tmp;
        plik>>tmp;
        name = decrypt_line(tmp);
        plik>>tmp;
        password = decrypt_line(tmp);
    }
};

int main() {
    srand(time(nullptr));
    Tekran e;
    vector<TBaza_Hasel> databases;
    e.switch_view(0);
    int wybor_menu = 1;

    while (true) {
        int c = getch();
        if (c == 13) {
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
