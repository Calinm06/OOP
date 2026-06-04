#include "Pacient.h"
#include <stdexcept>

#include "Angajat.h"
#include "Logger.h"

Pacient::Pacient(int zi, int luna, int an, const std::vector<int>& cnpNou,
                 const std::string& numeNou, const std::string& afectiuneNoua,
                 double buget, int prioritate)
    : Persoana(zi, luna, an, cnpNou, numeNou), afectiune(afectiuneNoua),buget(buget), prioritate(prioritate) {
    if (afectiune.empty() && (buget != -1 && prioritate != -1))
        throw ExceptieStringGol("nu are afectiune\n",afectiune);
    Logger::getInstance().inregistreaza("S-a creat un pacient");
}

Pacient::Pacient(const Pacient &p)
    : Persoana(p), afectiune(p.afectiune), buget(p.buget), prioritate(p.prioritate) {
}

Pacient::~Pacient() {
}

Pacient &Pacient::operator=(const Pacient &p) {
    if (this == &p)
        return *this;
    Persoana::operator=(p);
    afectiune = p.afectiune;
    buget = p.buget;
    prioritate = p.prioritate;
    return *this;
}

void Pacient::setAfectiune(const std::string& afectiuneNoua) {
    afectiune = afectiuneNoua;
}

void Pacient::afiseazaDate() {
    Persoana::afiseazaDate();

    try {
        if (this->getAfectiune() != "")
            std::cout << "Pacientul are boala " << getAfectiune() << "\n";
    }
    catch (ExceptieStringGol& e) {
        std::cout<<e.what();
    }
    std::cout << "Pacientul are un buget de " << buget << "\n";
    std::cout << "Pacientul are o prioritate de " << prioritate << "\n";
}

void Pacient::afiseazaDomeniuActivitate() {
    std::cout << "Nu cunoastem domeniul de activitate al pacientului\n";
}

double Pacient::calculeazaVenit() {
    return buget;
}

std::istream &operator>>(std::istream &is, Pacient &p) {
    is >> static_cast<Persoana&>(p);

    is.ignore(10, '\n');
    std::cout << "Introdu bugetul si prioritatea pacientului:\n";
    is >> p.buget >> p.prioritate;

    std::cout << "Introdu boala:\n";
    std::string boala;
    is >> boala;
    p.setAfectiune(boala);

    return is;
}

std::ostream& operator<<(std::ostream& os, Pacient& p) {
    os << static_cast<Persoana&>(p);

    try {
        os << "Pacientul are boala " << p.getAfectiune() << "\n";
    }
    catch (ExceptieStringGol& e) {
        os<<e.what();
    }
    os << "Pacientul are un buget de " << p.buget << "\n";
    os << "Pacientul are o prioritate de " << p.prioritate << "\n";

    return os;
}

char &Pacient::operator[](int index) {
    if (index >= 0 && index < afectiune.size())
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
