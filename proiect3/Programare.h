#pragma once
#include "Doctor.h"
#include "Pacient.h"
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

template <typename T, int durataMin = 120>
class Programare {
private:
    Pacient pacient;
    Doctor doctor;
    T tipProgramare;
    int durata;
    std::string detalii;

public:
    Programare(Pacient p,Doctor d,T tip,int durata,std::string detalii)
        :pacient(p),doctor(d),tipProgramare(tip),durata(durata),detalii(detalii) {
        if (durata <= 0)
            throw std::out_of_range("durata prea mica\n");
    }

    T getTipProgramare() const{return tipProgramare;}
    void setTipProgramare(T tipNou){tipProgramare = tipNou;}
    const std::string& getDetalii() const { return detalii; }
    void setDetalii(const std::string& d) { detalii = d; }
    Pacient getPacient() const { return pacient; }
    void setPacient(const Pacient& p) { pacient = p; }
    Doctor getDoctor() const { return doctor; }
    void setDoctor(const Doctor& d) { doctor = d; }
    int getDurata() const{return durata;}
    void setDurata(const int d){durata  = d;}

    template<typename U>
    void adaugaDetalii(const U& informatie) {
        std::ostringstream oss;
        oss<<informatie;
        detalii += "|" + oss.str();
    }


};
template<typename T,int N>
void sorteaza(std::vector<Programare<T,N>>& a) {
    if (a.empty())
        return;
    for (int i = 0;i < a.size() - 1;i++) {
        for (int j = i + 1;j < a.size();j++)
            if (a[i].getDurata() > a[j].getDurata())
                std::swap(a[i],a[j]);
    }
}

template<typename T,int N>
int numaraDupaTip(std::vector<Programare<T,N>>& a,const T& tip) {
    int count = 0;
    for (int i = 0;i < a.size();i++)
        if (a[i].getTipProgramare() == tip)
            count++;
    return count;
}

template<>
void sorteaza<std::string,120>(std::vector<Programare<std::string,120>>& a) {
    if (a.empty())
        return;
    for (int i = 0;i < a.size() - 1;i++) {
        for (int j = i + 1;j < a.size();j++)
            if (a[i].getDurata() > a[j].getDurata())
                std::swap(a[i],a[j]);
    }
}