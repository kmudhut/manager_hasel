#pragma once
#include <iostream>
#include <vector>

struct TBaza_Hasel {
private:
    std::string name;
    std::string password;
    std::vector<std::vector<std::string>> data;
public:
    TBaza_Hasel();
    TBaza_Hasel(std::string filename);
    std::string encrypt_line(std::string line) const;
    std::string decrypt_line(std::string line) const;
    std::string generate_password(int length, bool upper_case, bool lower_case, bool digits, bool special_characters);
    void export_data_base_to_file() const;
    void import_data_base_from_file(std::string filename);
    void display_data_base();
};


