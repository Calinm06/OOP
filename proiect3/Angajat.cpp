#include "Angajat.h"
#include "Persoana.h"
#include "DataCalendaristica.h"
#include <iostream>
#include <stdexcept>

#include "Logger.h"

Angajat::Angajat(int zi, int luna, int an, const std::vector<int>& cnpNou,
                 const std::string& numeNou, int idAngajat, double salariu,
                 const std::string& domeniu)
    : Persoana(zi, luna, an, cnpNou, numeNou), idAngajat(idAngajat), salariu(salariu),domeniu(domeniu) {
    if (domeniu.empty() && (idAngajat != -1 || salariu != -1))
        throw ExceptieStringGol("nu are domeniu\n",domeniu);
    Logger::getInstance().inregistreaza("S-a creeat un angajat");
}

Angajat::~Angajat() {
    std::cout << "Destructor Angajat\n";
}

Angajat::Angajat(const Angajat &a)
    : Persoana(a), idAngajat(a.idAngajat), salariu(a.salariu), domeniu(a.domeniu) {
}

Angajat& Angajat::operator=(const Angajat& a) {
    if (this == &a)
        return *this;

    Persoana::operator=(a);

    idAngajat = a.idAngajat;
    salariu = a.salariu;
    domeniu = a.domeniu;

    return *this;
}


void Angajat::setDomeniu(const std::string& domeniuNou) {
    domeniu = domeniuNou;
}

void Angajat::afiseazaDate() {
    Persoana::afiseazaDate();
    std::cout << "Id-ul angajatului este " << idAngajat << "\n";
    std::cout << "Salariul angajatului este " << salariu << "\n";

    try {
        std::cout<<"Domeniul angajatului este "<<getDomeniu()<<"\n";
    }
    catch (ExceptieStringGol& e){
        std::cout<<e.what();
    }
}

double Angajat::calculeazaVenit() {
    return salariu;
}

void Angajat::afiseazaDomeniuActivitate() {
    std::cout << "Angajatul lucreaza in domeniul " << domeniu << " ,dar nu are o specializare\n";
}


std::istream &operator>>(std::istream &is, Angajat &a) {
    is >> static_cast<Persoana&>(a);

    is.ignore(10, '\n');
    std::cout << "Introdu Id-ul de angajat si salariul\n";
    int id, sal;
    is >> id >> sal;
    a.setIdAngajat(id);
    a.setSalariu(sal);

    std::cout << "Introdu domeniul angajatului\n";
    std::string domeniu;
    is >> domeniu;
    a.setDomeniu(domeniu);

    return is;
}

std::ostream& operator<<(std::ostream& os, Angajat& a) {
    os << static_cast<Persoana&>(a);
    os << "Id-ul de angajat este " << a.getIdAngajat() << '\n';
    os << "Salariul angajatului este " << a.getSalariu() << "\n";
    try {
        os<<"Domeniul angajatului este "<<a.getDomeniu()<<"\n";
    }
    catch (ExceptieStringGol& e){
        os<<e.what();
    }

    return os;
}

char &Angajat::operator[](int index) {
    if (index >= 0 && index < domeniu.size())
        return domeniu[index];
    throw std::out_of_range("index invalid");
}

Angajat &Angajat::operator++() {
    salariu++;
    return *this;
}

Angajat Angajat::operator+(const double marire) {
    Angajat sol = *this;
    sol.salariu += marire;
    return sol;
}

Angajat Angajat::operator-(const double micsorare) {
    Angajat sol = *this;
    sol.salariu -= micsorare;
    return sol;
}

bool Angajat::operator==(const Angajat &a) {
    return idAngajat == a.idAngajat;
}

bool Angajat::operator<(const Angajat &a) {
    return salariu < a.salariu;
}
