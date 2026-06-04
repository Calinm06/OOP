#include "Persoana.h"
#include "DataCalendaristica.h"
#include <iostream>
#include <stdexcept>

#include "Logger.h"

Persoana::Persoana(int zi, int luna, int an, const std::vector<int>& cnpNou, const std::string& numeNou)
    : dataNasterii(zi, luna, an), cnp(cnpNou), nume(numeNou) {
    if (cnp.size() != 13 &&(zi != -1 || luna != -1 || an != -1 || nume.empty() == false))
        throw ExceptieCnpInvalid("cnp invalid\n",cnp);
    if (nume.empty() &&(zi != -1 || luna != -1 || an != -1))
        throw  ExceptieStringGol("nu are nume\n",nume);
    Logger::getInstance().inregistreaza("S-a creat o persoana");
}

Persoana::Persoana(const Persoana &p)
    : cnp(p.cnp), dataNasterii(p.dataNasterii), nume(p.nume) {
}

Persoana& Persoana::operator=(const Persoana& p) {
    if (this == &p)
        return *this;
    cnp = p.cnp;
    dataNasterii = p.dataNasterii;
    nume = p.nume;
    return *this;
}

Persoana::~Persoana() {
    std::cout << "Destructor persoana\n";
}

std::ostream &operator<<(std::ostream &os, const Persoana &p) {
    try {
        os<<"persoana are numele "<<p.getNume()<<"\n";
    }
    catch (const ExceptieStringGol&) {
        os<<"persoana nu are nume\n";
    }

    try {
        os << "CNP-ul este ";
        for (int digit : p.getCnp())
            os << digit;
        os << "\n";
    }
    catch (ExceptieCnpInvalid& e) {
        os<<e.what();
    }

    os << "Data Nasterii este " << p.dataNasterii;
    return os;
}

std::istream &operator>>(std::istream &is, Persoana &p) {
    std::cout << "Introdu cnp(13 cifre)\n";
    std::string aux;
    is >> aux;
    std::vector<int> cnp(13,0);
    if (aux.size() == 13) {
        for (int i = 0; i < 13; i++)
            cnp[i] = aux[i] - '0';
    }
    else {
        std::cout<<"Cnp invalid\n";
        return is;
    }
    p.setCnp(cnp);


    std::cout << "Introdu ziua de nastere(zi,luna,an)\n";
    int zi, luna, an;
    is >> zi >> luna >> an;
    p.setDataNasterii({zi, luna, an});

    std::cout << "Introdu numele\n";
    std::string nume;
    is >> nume;
    p.setNume(nume);

    return is;
}

void Persoana::setCnp(const std::vector<int>& cnpNou) {
    cnp = cnpNou;
}

void Persoana::setNume(const std::string& numeNou) {
    nume = numeNou;
}

void Persoana::afiseazaDate() {
    std::cout << *this;
}



