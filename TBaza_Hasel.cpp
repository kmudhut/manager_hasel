#include "TBaza_Hasel.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <fstream>
#include <random>

using namespace std;

TBaza_Hasel::TBaza_Hasel() {
    cout << "Podaj nazwę nowej bazy haseł:";
    string new_database_name;
    cin >> new_database_name;
    name = new_database_name;
    cout << "Utwórz hasło nowej bazy:";
    string new_database_password;
    int c;
    while ((c = getch()) != 13) {
        if (c < 32) {
            if (c == 8 && new_database_password[0]) {
                new_database_password.pop_back();
                putch('\b');
                putch(' ');
                putch('\b');
            }
            continue;
        }
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
            bool special_characters = ((c == 't') ? true : false);

            cout << "\n\tHasło:" << (tmp[2] = generate_password(length, upper_case, lower_case, digits,
                                                                special_characters));
            cin.get();
        }


        data.push_back(tmp);

        cout << endl <<
                "Wpis został dodany do bazy haseł. Zakończ wprowadzanie - ESC, kontynuuj - dowolny przycisk.";
    }
    while (getch() != 27);
    export_data_base_to_file();
};

TBaza_Hasel::TBaza_Hasel(string filename) {
    import_data_base_from_file(filename);
}

string TBaza_Hasel::encrypt_line(string line) const {
    string encrypted_line;
    for (int i = 0, j = 0; i < line.size(); ++i) {
        if (i % 2 == 0) {
            encrypted_line.push_back(line.at(i) + 1);
            string random;
            for (int i = 0; i < 10; i++) {
                random_device rd;
                mt19937 mt(rd());
                uniform_int_distribution<int> random_number(33, 255);
                random.push_back(random_number(mt));
               
            }
            encrypted_line.insert(encrypted_line.length(), random);
        }
        else encrypted_line.push_back(line.at(i) - 1);
    }
    return encrypted_line;
}

string TBaza_Hasel::decrypt_line(string line) const {
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

string TBaza_Hasel::generate_password(int length, bool upper_case, bool lower_case, bool digits, bool special_characters) {
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

    for (int i = 0; i < length; ++i) {
        random_device rd;
        mt19937 mt(rd());
        uniform_int_distribution<int> random(0, charset.size() - 1);
        generated_password.push_back(charset.at(random(mt)));
    }

    return generated_password;
}

void TBaza_Hasel::export_data_base_to_file() const {
    ofstream plik;
    plik.open(name + ".mudhut");
    plik << encrypt_line(name) << endl;
    plik << encrypt_line(password) << endl;
    plik << encrypt_line(to_string(data.size())) << endl;
    for (const auto&wpis: data) {
        for (const auto&elem: wpis) {
            plik << encrypt_line(elem) << endl;
        }
    }
    plik.close();
}

void TBaza_Hasel::import_data_base_from_file(string filename) {
    ifstream plik;
    plik.open(filename);
    string tmp;
    getline(plik, tmp);
    name = decrypt_line(tmp);
    getline(plik, tmp);

    password = decrypt_line(tmp);
    getline(plik, tmp);
    unsigned long long amount_of_records = stoull(decrypt_line(tmp));
    for (unsigned long long i = 0; i < amount_of_records; ++i) {
        vector<string> record;
        for (int j = 0; j < 3; ++j) {
            getline(plik, tmp);
            record.push_back(decrypt_line(tmp));
        }
        data.push_back(record);
    }
    plik.close();
}

void TBaza_Hasel::display_data_base() {
    string password_passed_by_user;
    do {
        system("cls");
        cout << "Wprowadź hasło do bazy danych:";
        password_passed_by_user.clear();
        int c;
        while ((c = getch()) != 13) {
            if (c < 32) {
                if (c == 8 && password_passed_by_user[0]) {
                    password_passed_by_user.pop_back();
                    putch('\b');
                    putch(' ');
                    putch('\b');
                }
                continue;
            }
            putch('*');
            password_passed_by_user.push_back(c);
        }
    }
    while (password_passed_by_user != password);
    system("cls");
    cout << "BAZA HASEŁ: " << name << endl << "Wciśnij [ESC] by powrócić do menu głównego." << endl << endl;
    for (const auto record: data) {
        cout << record[0] << endl;
        cout << "\tLogin: " << record[1] << endl;
        cout << "\tHasło: " << record[2] << endl;
    }
    while (getch() != 27);
}
