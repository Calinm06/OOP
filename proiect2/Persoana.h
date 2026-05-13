#pragma once
#include <cstring>
#include <iostream>

#include "DataCalendaristica.h"


class Persoana {
private:
    int* cnp;
    DataCalendaristica dataNasterii;
protected:
    char* nume;
public:
    virtual double calculeazaVenit() = 0;
    virtual void afiseazaDomeniuActivitate() = 0;

    //constructori destructori
    Persoana(int zi = -1,int luna = -1,int an = -1,int* cnpNou = nullptr,char* numeNou = nullptr);
    virtual ~Persoana();
    Persoana(const Persoana& p);

    //setteri si getteri
    int* getCnp()const {return cnp;}
    DataCalendaristica getDataNastere()const {return dataNasterii;}
    const char* getNume() const{return nume;}
    void setCnp(const int* cnpNou);
    void setDataNasterii(const DataCalendaristica& dataNoua){dataNasterii = dataNoua;}
    void setNume(const char* numeNou);

    //suprascriere operatori
    Persoana& operator=(const Persoana& p);
    friend std::ostream& operator<<(std::ostream& os,const Persoana& p);
    friend std::istream& operator>>(std::istream& is,Persoana& p);

    //functii proprii
    virtual void afiseazaDate();
};


