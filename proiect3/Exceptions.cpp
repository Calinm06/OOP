//
// Created by calin on 13/05/2026.
//

#include "Exceptions.h"

Exceptions::Exceptions(const std::string &mesaj)
    :std::runtime_error(mesaj),mesaj(mesaj){}

const char *Exceptions::what() const noexcept {
    return mesaj.c_str();
}

ExceptieCnpInvalid::ExceptieCnpInvalid(const std::string& mesaj,const std::vector<int> &cnp)
:Exceptions(mesaj),cnp(cnp) {
    this->mesaj += " (CNP invalid: ";
    for (int cifra : this->cnp) {
        this->mesaj += std::to_string(cifra);
    }
    this->mesaj += ")";
}

const char* ExceptieCnpInvalid::what() const noexcept {
    return mesaj.c_str();
}


ExceptieStringGol::ExceptieStringGol(const std::string &mesaj, const std::string &str)
    :Exceptions(mesaj),str(str){
    this->mesaj += "string gol";
}

const char* ExceptieStringGol::what() const noexcept {
    return mesaj.c_str();
}
