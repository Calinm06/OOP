#include "Persoana.h"
#include "DataCalendaristica.h"
#include <cstring>
#include <iostream>
#include <stdexcept>

Persoana:: Persoana(int zi,int luna,int an,int* cnpNou ,char* numeNou)
        :dataNasterii(zi,luna,an) {
    if (cnpNou != nullptr) {
        cnp = new int [13];
        for (int i = 0;i < 13;i++)
            cnp[i] = cnpNou[i];
    }
    else
        cnp = nullptr;

    if (numeNou != nullptr) {
        nume = new char[strlen(numeNou) + 1];
        strcpy(nume,numeNou);
    }
    else
        nume = nullptr;
}

Persoana::Persoana(const Persoana &p)
:dataNasterii(p.dataNasterii){
    if (p.cnp != nullptr) {
        cnp = new int [13];
        for (int i = 0;i < 13;i++)
            cnp[i] = p.cnp[i];
    }
    else
        cnp = nullptr;

    if (p.nume != nullptr) {
        nume = new char[strlen(p.nume) + 1];
        strcpy(nume,p.nume);
    }
    else
        nume = nullptr;
}

Persoana& Persoana::operator=(const Persoana& p) {
    if (this == &p)
        return *this;

    if (nume != nullptr)
        delete [] nume;
    if (cnp != nullptr)
        delete [] cnp;
    cnp = nullptr;
    nume = nullptr;

    dataNasterii = p.dataNasterii;
    if (p.cnp != nullptr) {
        cnp = new int [13];
        for (int i = 0;i < 13;i++)
            cnp[i] = p.cnp[i];
    }
    else
        cnp = nullptr;

    if (p.nume != nullptr) {
        nume = new char[strlen(p.nume) + 1];
        strcpy(nume,p.nume);
    }
    else
        nume = nullptr;

    return *this;
}

Persoana::~Persoana() {
    std::cout<<"Destructor persoana\n";
    if (nume != nullptr)
        delete [] nume;
    if (cnp != nullptr)
        delete [] cnp;
    cnp = nullptr;
    nume = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Persoana &p) {
    if (p.nume != nullptr)
        os<<"Numele este "<<p.nume<<"\n";
    else
        os<<"Persoana nu are nume\n";
    if (p.cnp != nullptr) {
        os<<"CNP-ul este ";
        for (int i = 0;i < 13;i++)
            os<<p.cnp[i];
        os<<"\n";
    }
    else
        os<<"Persoana nu are cnp\n";

    os<<"Data Nasterii este "<<p.dataNasterii;
    return os;
}

std::istream &operator>>(std::istream &is, Persoana &p) {
    std::cout<<"Introdu cnp(13 cifre)\n";
    char aux[13];
    is>>aux;
    int cnp[13];
    for (int i = 0;i < 13;i++)
        cnp[i] = aux[i] - '0';
    p.setCnp(cnp);

    std::cout<<"Introdu ziua de nastere(zi,luna,an)\n";
    int zi,luna,an;
    is>>zi>>luna>>an;
    p.setDataNasterii({zi,luna,an});

    std::cout<<"Introdu numele\n";
    char nume[100];
    is>>nume;
    p.setNume(nume);

    return is;
}

void Persoana::setCnp(const int *cnpNou) {
    if (cnp != nullptr)
        delete [] cnp;
    cnp = nullptr;
    if (cnpNou != nullptr) {
        cnp = new int[13];
        for (int i = 0;i < 13;i++)
            cnp[i] = cnpNou[i];
    }
}

void Persoana::setNume(const char *numeNou) {
    if (nume != nullptr)
        delete[] nume;
    nume = nullptr;
    if (numeNou != nullptr) {
        nume = new char[strlen(numeNou) + 1];
        strcpy(nume,numeNou);
    }
}

void Persoana::afiseazaDate() {
    std::cout<<*this;
}
