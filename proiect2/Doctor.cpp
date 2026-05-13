#include "Doctor.h"
#include "Angajat.h"
#include <cstring>
#include <stdexcept>
Doctor::Doctor(int zi, int luna, int an, int *cnpNou, char *numeNou, int idAngajat, double salariu, char *domeniu, char *specializare, double pretConsultatie, double sporVechime)
    :Angajat(zi,luna,an,cnpNou,numeNou,idAngajat,salariu,domeniu),pretConsultatie(pretConsultatie),sporVechime(sporVechime) {
    if (specializare != nullptr) {
        this->specializare = new char [strlen(specializare) + 1];
        strcpy(this->specializare,specializare);
    }else
        this->specializare = nullptr;

}

Doctor::~Doctor() {
    std::cout<<"Destructor Doctor\n";
    if (specializare != nullptr)
        delete[] specializare;
    specializare = nullptr;
}

Doctor::Doctor(const Doctor &d)
    :Angajat(d),pretConsultatie(d.pretConsultatie),sporVechime(d.sporVechime) {
    if (d.specializare != nullptr) {
        specializare = new char[strlen(d.specializare) + 1];
        strcpy(specializare,d.specializare);
    }else
        specializare = nullptr;

}

Doctor& Doctor::operator=(const Doctor& d) {
    if (this == &d)
        return *this;
    Angajat::operator=(d);
    pretConsultatie = d.pretConsultatie;
    sporVechime = d.sporVechime;
    if (specializare != nullptr)
        delete[] specializare;

    if (d.specializare != nullptr) {
        specializare = new char[strlen(d.specializare) + 1];
        strcpy(specializare,d.specializare);
    }else
        specializare = nullptr;

    return *this;
}

void Doctor::setSpecializare(const char *specializareNoua) {
    if (specializare != nullptr)
        delete[] specializare;

    if (specializareNoua != nullptr) {
        specializare = new char[strlen(specializareNoua) + 1];
        strcpy(specializare,specializareNoua);
    }else
        specializare = nullptr;
}

void Doctor::afiseazaDate() {
    Angajat::afiseazaDate();
    if (specializare == nullptr)
        std::cout<<"Doctorul nu are specializare\n";
    else
        std::cout<<"Doctorul are specializare "<<specializare<<"\n";
    std::cout<<"Doctorul are pretul consultatiei "<<pretConsultatie<<" de lei\n";
    std::cout<<"Doctorul are un spor de vechime de "<<sporVechime<<"\n";

}

double Doctor::calculeazaVenit() {
    int nrConsultatii = salariu / pretConsultatie;
    double bonus = nrConsultatii * sporVechime;
    return salariu + bonus;
}

void Doctor::afiseazaDomeniuActivitate() {
    std::cout<<"Doctorul activeaza in domeniul "<<domeniu<<" avand specializarea de "<<specializare<<"\n";
}


std::istream &operator>>(std::istream &is, Doctor &d) {
    is>>static_cast<Angajat&>(d);

    is.ignore(10,'\n');
    std::cout<<"Introdu pretul consultatei si sporul de vechime:\n";
    double pret,spor;
    is>>pret>>spor;
    d.setPretConsultatie(pret);
    d.setSporVechime(spor);

    std::cout<<"Intordu specializarea: \n";
    char specizare[100];
    is>>specizare;
    d.setSpecializare(specizare);

    return is;
}

std::ostream& operator<<(std::ostream& os,Doctor& d) {
    os<<static_cast<Angajat &>(d);
    if (d.specializare == nullptr)
        os<<"Doctorul nu are specializare\n";
    else
        os<<"Doctorul are specializare "<<d.specializare<<"\n";
    os<<"Doctorul are pretul consultatiei "<<d.pretConsultatie<<" de lei\n";
    os<<"Doctorul are un spor de vechime de "<<d.sporVechime<<"\n";

    return os;
}

char &Doctor::operator[](int index) {
    if (specializare != nullptr && index >= 0 && index < strlen(specializare))
        return specializare[index];
    throw std::out_of_range("index invalid");
}

Doctor &Doctor::operator++() {
    pretConsultatie++;
    return *this;
}

Doctor Doctor::operator+(const int marire) {
    Doctor sol = *this;
    sol.pretConsultatie += marire;
    return sol;
}

Doctor Doctor::operator-(const int micsorare) {
    Doctor sol = *this;
    sol.pretConsultatie -= micsorare;
    return sol;
}

bool Doctor::operator==(const Doctor &d) {
    return d.idAngajat == idAngajat;
}

bool Doctor::operator<(const Doctor &d) {
    if (pretConsultatie == d.pretConsultatie)
        return sporVechime < d.sporVechime;
    else
        return pretConsultatie < d.pretConsultatie;
}

