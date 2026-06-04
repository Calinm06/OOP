#pragma once
#include "Angajat.h"
#include "Persoana.h"
#include "DataCalendaristica.h"
#include <string>

class Doctor : public Angajat {
protected:
    std::string specializare;
    double pretConsultatie;
    double sporVechime;
public:
    //destructori si constructori
    Doctor(int zi = -1, int luna = -1, int an = -1, const std::vector<int>& cnpNou = {},
           const std::string& numeNou = "", int idAngajat = -1, double salariu = -1.0,
           const std::string& domeniu = "", const std::string& specializare = "",
           double pretConsultatie = -1, double sporVechime = 0);
    virtual ~Doctor();
    Doctor(const Doctor& d);

    //setteri si getteri
    const std::string& getSpecializare() const { if (specializare.empty()) throw ExceptieStringGol("nu are specializare",specializare); else return specializare; }
    double getPretConsultatie() const { return pretConsultatie; }
    double getSporVechime() const { return sporVechime; }
    void setSpecializare(const std::string& specializareNoua);
    void setPretConsultatie(double pretNou) { pretConsultatie = pretNou; }
    void setSporVechime(double sporNou) { sporVechime = sporNou; }

    //suprascriere de operatori
    Doctor& operator=(const Doctor& d);
    friend std::istream& operator>>(std::istream& is, Doctor& d);
    friend std::ostream& operator<<(std::ostream& os, Doctor& d);
    char& operator[](int index);
    Doctor& operator++();
    Doctor operator+(const int marire);
    Doctor operator-(const int micsorare);
    bool operator<(const Doctor& d);
    bool operator==(const Doctor& d);

    //functii proprii
    virtual void afiseazaDate() override;
    double calculeazaVenit() override;
    void afiseazaDomeniuActivitate() override;
};
