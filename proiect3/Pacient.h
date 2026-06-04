#pragma once
#include "Persoana.h"
#include <string>
#include "Exceptions.h"

class Pacient final: public Persoana{ //clasa Pacient este final, deoarece nu mai are sens sa derivam din ea
private:
    std::string afectiune;
    double buget;
    int prioritate;
public:
    //constructori si destructori
    Pacient(int zi = -1, int luna = -1, int an = -1, const std::vector<int>& cnpNou = {},
            const std::string& numeNou = "", const std::string& afectiuneNoua = "",
            double buget = -1, int prioritate = -1);
    virtual ~Pacient();
    Pacient(const Pacient& p);

    //setteri si getteri
    const std::string& getAfectiune() const { if (afectiune.empty()) throw ExceptieStringGol("nu are afectiune",afectiune); else return afectiune; }
    double getBuget() const { return buget; }
    int getPrioritate() const { return prioritate; }
    void setAfectiune(const std::string& afectiuneNoua);
    void setBuget(const double bugetNou) { buget = bugetNou; }
    void setPrioritate(int prior) { prioritate = prior; }

    //suprascriere operatori
    Pacient& operator=(const Pacient& p);
    friend std::istream& operator>>(std::istream& is, Pacient& p);
    friend std::ostream& operator<<(std::ostream& os, Pacient& p);
    char& operator[](int index);
    Pacient&operator++();
    Pacient operator+(const int marire);
    Pacient operator-(const int micsorare);
    bool operator<(const Pacient& p);

    //functii proprii
    double calculeazaVenit() override;
    void afiseazaDomeniuActivitate() override;
    void afiseazaDate() override;
};
