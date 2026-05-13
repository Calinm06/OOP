#include "Pacient.h"
#include <cstring>
#include <stdexcept>

#include "Angajat.h"

Pacient::Pacient(int zi, int luna, int an, int *cnpNou, char *numeNou, char *afectiuneNoua, double buget, double prioritate)
    :Persoana(zi,luna,an,cnpNou,numeNou),buget(buget),prioritate(prioritate){
    if (afectiuneNoua != nullptr) {
        afectiune = new char[strlen(afectiuneNoua) + 1];
        strcpy(afectiune,afectiuneNoua);
    }
    else
        afectiune = nullptr;
}

Pacient::Pacient(const Pacient &p)
    :Persoana(p),buget(p.buget),prioritate(p.prioritate) {
    if (p.afectiune != nullptr) {
        afectiune = new char[strlen(p.afectiune) + 1];
        strcpy(afectiune,p.afectiune);
    }
    else
        afectiune = nullptr;
}

Pacient::~Pacient() {
    if (afectiune != nullptr)
        delete[] afectiune;
    afectiune = nullptr;
}

Pacient &Pacient::operator=(const Pacient &p) {
    if (this == &p)
        return *this;
    Persoana::operator=(p);
    buget = p.buget;
    prioritate = p.prioritate;

    if (afectiune != nullptr)
        delete[] afectiune;
    afectiune = nullptr;
    if (p.afectiune != nullptr) {
        afectiune = new char[strlen(p.afectiune) + 1];
        strcpy(afectiune,p.afectiune);
    }
    return *this;
}

void Pacient::setAfectiune(const char *afectiuneNoua) {
    if (afectiune != nullptr)
        delete[] afectiune;
    afectiune = nullptr;
    if (afectiuneNoua != nullptr) {
        afectiune = new char[strlen(afectiuneNoua) + 1];
        strcpy(afectiune,afectiuneNoua);
    }
}

void Pacient::afiseazaDate() {
    Persoana::afiseazaDate();
    if (afectiune != nullptr)
        std::cout<<"Pacientul are boala "<<afectiune<<"\n";
    else
        std::cout<<"Pacientul e sanatos\n";
    std::cout<<"Pacientul are un buget de "<<buget<<"\n";
    std::cout<<"Paceintul are o prioritate de "<<prioritate<<"\n";
}

void Pacient::afiseazaDomeniuActivitate() {
    std::cout<<"Nu cunoastem domeniul de activitate al pacientului\n";
}

double Pacient::calculeazaVenit() {
    return buget;
}

std::istream &operator>>(std::istream &is, Pacient &p) {
    is>>static_cast<Persoana&>(p);

    is.ignore(10,'\n');
    std::cout<<"Introdu bugetul si prioritatea pacientului:\n";
    is>>p.buget>>p.prioritate;

    std::cout<<"Introdu boala:\n";
    char boala[100];
    is>>boala;
    p.setAfectiune(boala);

    return is;
}

std::ostream& operator<<(std::ostream& os,Pacient& p) {
    os<<static_cast<Persoana&>(p);

    if (p.afectiune != nullptr)
        os<<"Pacientul are boala "<<p.afectiune<<"\n";
    else
        os<<"Pacientul e sanatos\n";
    os<<"Pacientul are un buget de "<<p.buget<<"\n";
    os<<"Paceintul are o prioritate de "<<p.prioritate<<"\n";

    return os;
}

char &Pacient::operator[](int index) {
    if (afectiune != nullptr && index >= 0 && index < strlen(afectiune))
        return afectiune[index];

    throw std::out_of_range("index invalid");
}

Pacient &Pacient::operator++() {
    buget++;
    return *this;
}

Pacient Pacient::operator+(const int marire) {
    Pacient sol = *this;
    sol.buget += marire;
    return sol;
}

Pacient Pacient::operator-(const int micsorare) {
    Pacient sol = *this;
    sol.buget -= micsorare;
    return sol;
}

bool Pacient::operator<(const Pacient &p) {
    return prioritate < p.prioritate;
}
