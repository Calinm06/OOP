#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "DataCalendaristica.h"
#include "Exceptions.h"

class Persoana {
private:
    std::vector<int> cnp;
    DataCalendaristica dataNasterii;
protected:
    std::string nume;
public:
    virtual double calculeazaVenit() = 0;
    virtual void afiseazaDomeniuActivitate() = 0;

    //constructori destructori
    Persoana(int zi = -1, int luna = -1, int an = -1, const std::vector<int>& cnpNou = {}, const std::string& numeNou = "");
    virtual ~Persoana();
    Persoana(const Persoana& p);

    //setteri si getteri
    const std::vector<int>& getCnp() const { if (cnp.size() != 13) throw ExceptieCnpInvalid("cnp invalid",cnp); else return cnp; }
    DataCalendaristica getDataNastere() const { return dataNasterii; }
    const std::string& getNume() const { if (nume.empty()) throw ExceptieStringGol("nume invalid",nume); else return nume; }
    void setCnp(const std::vector<int>& cnpNou);
    void setDataNasterii(const DataCalendaristica& dataNoua) { dataNasterii = dataNoua; }
    void setNume(const std::string& numeNou);

    //suprascriere operatori
    Persoana& operator=(const Persoana& p);
    friend std::ostream& operator<<(std::ostream& os, const Persoana& p);
    friend std::istream& operator>>(std::istream& is, Persoana& p);

    //functii proprii
    virtual void afiseazaDate();
};
