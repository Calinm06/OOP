#pragma once
#include <string>
#include <vector>

class IReteta {
protected:
    std::string numePacient;
    std::string medicament;
public:
    IReteta(std::string numePacient,std::string medicament)
        :numePacient(numePacient),medicament(medicament) {}
    virtual ~IReteta() = default;
    virtual void afiseazaReteta() const = 0;
};


class RetetaStandard : public IReteta {
public:
    RetetaStandard(std::string nume,std::string med)
        :IReteta(nume,med){}
    void afiseazaReteta() const override;
};

class RetetaPremium : public IReteta {
public:
    RetetaPremium(std::string nume,std::string med)
        :IReteta(nume,med){}
    void afiseazaReteta() const override;
};


class IFisaMedicala {
protected:
    std::vector<std::string> istoric;
public:
    IFisaMedicala(std::vector<std::string> istoric)
        :istoric(istoric){}
    virtual ~IFisaMedicala() = default;

    virtual void afiseazaFisa() const = 0;
};

class FisaMedicalaStandard : public IFisaMedicala{
public:
    FisaMedicalaStandard(std::vector<std::string> istoric)
        :IFisaMedicala(istoric){}
    virtual ~FisaMedicalaStandard() = default;

    void afiseazaFisa() const override;
};

class FisaMedicalaPremium : public IFisaMedicala{
public:
    FisaMedicalaPremium(std::vector<std::string> istoric)
        :IFisaMedicala(istoric){}
    virtual ~FisaMedicalaPremium() = default;

    void afiseazaFisa() const override;
};


class IDocumentFactory {
public:
    virtual ~IDocumentFactory() = default;
    virtual IReteta* creazaReteta(std::string nume,std::string med) const  = 0;
    virtual IFisaMedicala* creazaFisaMedicala(std::vector<std::string> istoric) const  = 0;
};

class StandardFactory : public IDocumentFactory{
public:
    virtual ~StandardFactory() = default;
    IReteta* creazaReteta(std::string nume,std::string med)const override {
        return new RetetaStandard(nume,med);
    };
    IFisaMedicala* creazaFisaMedicala(std::vector<std::string> istoric)const override {
        return new FisaMedicalaStandard(istoric);
    }
};

class PremiumFactory : public IDocumentFactory{
public:
    virtual ~PremiumFactory() = default;
    IReteta* creazaReteta(std::string nume,std::string med)const override {
        return new RetetaPremium(nume,med);
    };
    IFisaMedicala* creazaFisaMedicala(std::vector<std::string> istoric)const override {
        return new FisaMedicalaPremium(istoric);
    }
};

class DocumenteClient {
private:
    const IDocumentFactory* fabrica;
public:
    DocumenteClient(IDocumentFactory* fabrica)
        :fabrica(fabrica){}
    void setFabrica(IDocumentFactory* f){fabrica = f;}

    void proceseazaPacient(std::string nume,std::string medicament,std::vector<std::string>istoric);
};