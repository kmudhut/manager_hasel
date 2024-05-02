//
// Created by Kamil on 02.05.2024.
//

#ifndef MANAGER_HASEL_TBLAD_H
#define MANAGER_HASEL_TBLAD_H
#include <iostream>
enum Terror_seriousness {notknown, negligible, important, critical};

class TBlad {
protected:
    std::string message = "unknown";
    int code;
    Terror_seriousness seriousness = negligible;
public:
    TBlad(int cd = 0, Terror_seriousness srsns = notknown): code{cd}, seriousness{srsns}
    {

    }
    virtual void write_error_info(){
        std::cout<<"\n\nWystąpił jakiś błąd :/ To wszystko co wiemy.\n\n";
    }
    Terror_seriousness get_error_seriousness() {
        return seriousness;
    }
    int get_error_code() {
        return code;
    }
};

class TBlad_OtwarciaPliku : public TBlad {
private:
    std::string filename;
public:
    TBlad_OtwarciaPliku(std::string filename = "unknown") : TBlad(1, critical)
    {
        this->filename = filename;
        message = "Nie udało się otworzyć pliku " + this->filename;
    }
    void write_error_info() override{

        std::cout<<"\n\nBŁĄD "<<code<< ((seriousness == critical)?" (KRYTYCZNY!)":"");
        std::cout<<std::endl<<message;
    }
};

class TBlad_ZakazanaNazwa : public TBlad {
private:
    std::string name;
public:
    TBlad_ZakazanaNazwa(std::string name = "unknown") : TBlad(2, important)
    {
        this->name = name;
        message = "Nie wolno używać brzydkich słów, takich jak: " + name + "!";
    }
    void write_error_info() override{

        std::cout<<"\n\nBŁĄD "<<code<< ((seriousness == critical)?" (KRYTYCZNY!)":"");
        std::cout<<std::endl<<message;
    }
};


#endif //MANAGER_HASEL_TBLAD_H
