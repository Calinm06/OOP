#pragma once
#include <stdexcept>
#include <string>
#include <vector>

class Exceptions  : public std::runtime_error{
protected:
    std::string mesaj;
public:
    explicit Exceptions(const std::string& mesaj);
    virtual const char* what() const noexcept override;
};

class ExceptieCnpInvalid : public Exceptions {
private:
    std::vector<int>cnp;
public:
    explicit ExceptieCnpInvalid(const std::string& mesaj,const std::vector<int>&cnp);
    virtual const char* what() const noexcept override;
};

class ExceptieStringGol : public Exceptions {
private:
    std::string str;
public:
    explicit ExceptieStringGol(const std::string& mesaj, const std::string& str);
    virtual const char* what() const noexcept override;
};