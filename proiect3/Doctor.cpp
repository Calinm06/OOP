#include "Doctor.h"
#include "Angajat.h"
#include <stdexcept>

#include "Logger.h"

Doctor::Doctor(int zi, int luna, int an, const std::vector<int>& cnpNou,
               const std::string& numeNou, int idAngajat, double salariu,
               const std::string& domeniu, const std::string& specializare,
               double pretConsultatie, double sporVechime)
    : Angajat(zi, luna, an, cnpNou, numeNou, idAngajat, salariu, domeniu),
      specializare(specializare), pretConsultatie(pretConsultatie), sporVechime(sporVechime) {
    if (specializare.empty() && (pretConsultatie != -1 || sporVechime))
        throw ExceptieStringGol("nu are specializare\n",specializare);
    Logger::getInstance().inregistreaza("S-a creat un doctor");
}

Doctor::~Doctor() {
    std::cout << "Destructor Doctor\n";
}

Doctor::Doctor(const Doctor &d)
    : Angajat(d), specializare(d.specializare), pretConsultatie(d.pretConsultatie),
      sporVechime(d.sporVechime) {
}

Doctor& Doctor::operator=(const Doctor& d) {
    if (this == &d)
        return *this;
    Angajat::operator=(d);
    specializare = d.specializare;
    pretConsultatie = d.pretConsultatie;
    sporVechime = d.sporVechime;
    return *this;
}

void Doctor::setSpecializare(const std::string& specializareNoua) {
    specializare = specializareNoua;
}

void Doctor::afiseazaDate() {
    Angajat::afiseazaDate();

    try {
        std::cout << "Doctorul are specializare " << getSpecializare() << "\n";
    }
    catch (ExceptieStringGol& e) {
        std::cout<<e.what();
    }

    std::cout << "Doctorul are pretul consultatiei " << pretConsultatie << " de lei\n";
    std::cout << "Doctorul are un spor de vechime de " << sporVechime << "\n";

}

double Doctor::calculeazaVenit() {
    int nrConsultatii = salariu / pretConsultatie;
    double bonus = nrConsultatii * sporVechime;
    return salariu + bonus;
}

void Doctor::afiseazaDomeniuActivitate() {
    std::cout << "Doctorul activeaza in domeniul " << domeniu << " avand specializarea de " << specializare << "\n";
}


std::istream &operator>>(std::istream &is, Doctor &d) {
    is >> static_cast<Angajat&>(d);

    is.ignore(10, '\n');
    std::cout << "Introdu pretul consultatei si sporul de vechime:\n";
    double pret, spor;
    is >> pret >> spor;
    d.setPretConsultatie(pret);
    d.setSporVechime(spor);

    std::cout << "Intordu specializarea: \n";
    std::string spec;
    is >> spec;
    d.setSpecializare(spec);

    return is;
}

std::ostream& operator<<(std::ostream& os, Doctor& d) {
    os << static_cast<Angajat&>(d);
    try {
        os << "Doctorul are specializare " << d.getSpecializare() << "\n";
    }
    catch (ExceptieStringGol& e) {
        os<<e.what();
    }

    os << "Doctorul are pretul consultatiei " << d.pretConsultatie << " de lei\n";
    os << "Doctorul are un spor de vechime de " << d.sporVechime << "\n";

    return os;
}

char &Doctor::operator[](int index) {
    if (index >= 0 && index < specializare.size())
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
