#include "Angajat.h"
#include "Persoana.h"
#include "DataCalendaristica.h"
#include <iostream>
#include <stdexcept>

Angajat::Angajat(int zi,int luna ,int an,int* cnpNou,char* numeNou,int idAngajat ,double salariu ,char* domeniu)
        :Persoana(zi,luna,an,cnpNou,numeNou),idAngajat(idAngajat),salariu(salariu) {
    if (domeniu != nullptr) {
        this->domeniu = new char[strlen(domeniu) + 1];
        strcpy(this->domeniu,domeniu);
    }
    else
        this->domeniu = nullptr;
}

Angajat::~Angajat() {
    std::cout<<"Destructor Angajat\n";
    if (domeniu != nullptr)
        delete [] domeniu;
    domeniu = nullptr;
}

Angajat::Angajat(const Angajat &a)
    :Persoana(a),idAngajat(a.idAngajat),salariu(a.salariu) {
    domeniu = new char[strlen(a.domeniu) + 1];
    strcpy(domeniu,a.domeniu);
}

Angajat& Angajat::operator=(const Angajat& a) {
    if (this == &a)
        return *this;

    Persoana::operator=(a);

    idAngajat = a.idAngajat;
    salariu = a.salariu;
    setDomeniu(a.domeniu);

    return *this;
}


void Angajat::setDomeniu(const char *domeniuNou) {
    if (domeniu != nullptr)
        delete []domeniu;
    domeniu = nullptr;
    if (domeniuNou != nullptr) {
        domeniu = new char[strlen(domeniuNou) + 1];
        strcpy(domeniu,domeniuNou);
    }
}

void Angajat::afiseazaDate() {
    Persoana::afiseazaDate();
    std::cout<<"Id-ul angajatului este "<<idAngajat<<"\n";
    std::cout<<"Salariul angajatului este "<<salariu<<"\n";
    if (domeniu == nullptr)
        std::cout<<"Angajatul nu are domeniu\n";
    else
        std::cout<<"Domeniul angajatului este "<<domeniu<<"\n";
}

double Angajat::calculeazaVenit() {
    return salariu;
}

void Angajat::afiseazaDomeniuActivitate() {
    std::cout<<"Angajatul lucreaza in domeniul "<<domeniu<<" ,dar nu are o specializare\n";
}


std::istream &operator>>(std::istream &is, Angajat &a) {
    is>>static_cast<Persoana&>(a);

    is.ignore(10,'\n');
    std::cout<<"Introdu Id-ul de angajat si salariul\n";
    int id,sal;
    is>>id>>sal;
    a.setIdAngajat(id);
    a.setSalariu(sal);

    std::cout<<"Introdu domeniul angajatului\n";
    char domeniu[100];
    is>>domeniu;
    a.setDomeniu(domeniu);

    return is;
}

std::ostream& operator<<(std::ostream& os,Angajat& a) {
    os<<static_cast<Persoana&>(a);
    os<<"Id-ul de angajat este "<<a.getIdAngajat()<<'\n';
    os<<"Salariul angajatului este "<<a.getSalariu()<<"\n";
    if (a.getDomeniu() != nullptr)
        os<<"Domeniul angajatului este "<<a.getDomeniu()<<"\n";
    else
        os<<"Angajatul nu are domeniu\n";

    return os;
}

char &Angajat::operator[](int index) {
    if (domeniu != nullptr && index >= 0 && index < strlen(domeniu))
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
