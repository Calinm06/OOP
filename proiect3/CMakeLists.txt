cmake_minimum_required(VERSION 3.20)
project(proiect2)

set(CMAKE_CXX_STANDARD 17)

# Adaugă și fișierele Persoana aici
add_executable(proiect2
        main.cpp
        DataCalendaristica.cpp
        DataCalendaristica.h
        Persoana.cpp
        Persoana.h
        Angajat.cpp
        Angajat.h
        Doctor.cpp
        Doctor.h
        Pacient.cpp
        Pacient.h
        Exceptions.cpp
        Exceptions.h
        Programare.cpp
        Programare.h
        Logger.cpp
        Logger.h
        AbstractFactory.cpp
        AbstractFactory.h
)