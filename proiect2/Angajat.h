#pragma once
#include "Persoana.h"

class Angajat : public Persoana{
protected:
    int idAngajat;
    double salariu;
    char* domeniu;
public:
    //constructori si destructori
    Angajat(int zi = -1,int luna = -1,int an = -1,int* cnpNou = nullptr,char* numeNou = nullptr,int idAngajat = -1,double salariu = -1,char* domeniu = nullptr);
    virtual ~Angajat();
    Angajat(const Angajat& a);

    //setteri si getteri
    int getIdAngajat() const{return idAngajat;}
    double getSalariu() const{return salariu;}
    const char* getDomeniu() const{return domeniu;}
    void setIdAngajat(int id) {idAngajat = id;}
    void setSalariu(double salariuNou){salariu = salariuNou;}
    void setDomeniu(const char* domeniuNou);

    //supraincarcare operatori
    Angajat& operator=(const Angajat& a);
    friend std::istream& operator>>(std::istream& is,Angajat&a);
    friend std::ostream& operator<<(std::ostream& os,Angajat& a);
    char& operator[](int index);
    Angajat& operator++();
    Angajat operator+(const double marire);
    Angajat operator-(const double micsorare);
    bool operator==(const Angajat& a);
    bool operator<(const Angajat& a);


    //functionalitai proprii
    virtual void afiseazaDate() override;
    double calculeazaVenit() override;
    void afiseazaDomeniuActivitate() override;
};

