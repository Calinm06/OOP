#include "AbstractFactory.h"
#include <iostream>


void RetetaStandard::afiseazaReteta() const {
    std::cout<<"Reteta standard pentru pacientul "<<numePacient<<" cu medicamentul "<<medicament<<"\n";
}

void RetetaPremium::afiseazaReteta() const {
    std::cout<<"Reteta premium pentru pacientul "<<numePacient<<" cu medicamentul "<<medicament<<"\n";
}

void FisaMedicalaStandard::afiseazaFisa() const {
    std::cout<<"Fisa medicala standard contine urmatoarele afectiuni\n";
    for (const auto& a : istoric)
        std::cout<<"-> "<<a<<"\n";
}


void FisaMedicalaPremium::afiseazaFisa() const {
    std::cout<<"Fisa medicala premium contine urmatoarele afectiuni\n";
    for (const auto& a : istoric)
        std::cout<<"-> "<<a<<"\n";
}

void DocumenteClient::proceseazaPacient(std::string nume, std::string medicament, std::vector<std::string> istoric) {
    IReteta* reteta = fabrica->creazaReteta(nume,medicament);
    IFisaMedicala* fisa_medicala = fabrica->creazaFisaMedicala(istoric);

    reteta->afiseazaReteta();
    fisa_medicala->afiseazaFisa();

    delete reteta;
    delete fisa_medicala;
}
