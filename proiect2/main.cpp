#include <iostream>

#include "Angajat.h"
#include "DataCalendaristica.h"
#include "Doctor.h"
#include "Pacient.h"
#include "Persoana.h"
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

#define debug 1
#if debug
std::ifstream fin("date.in");
#else
#define fin cin
#endif

bool incercareGasireDoctor(Persoana& p,int nrPacienti,Persoana* persoane[]) {
   try {
      Pacient& pacient = dynamic_cast<Pacient &>(p);// dynamic cast este preferat, deoarece la run time nu stim tipul obiectului
      const char* boala = pacient.getAfectiune();
      for (int i = 0;i < nrPacienti;i++) {
         Doctor* doctor = dynamic_cast<Doctor *>(persoane[i]);
         if (doctor != nullptr) {
            const char* specializare = doctor->getSpecializare();
            if (boala == nullptr || specializare == nullptr)
               continue;
            if (strcmp(boala,specializare) == 0) {
               std::cout<<"Pentru pacientul "<<pacient.getNume()<<" am gasit doctorul "<<doctor->getNume()<<"\n";
               return true;
            }

         }
      }
      return false;
   }
   catch (std::bad_cast& e) {
      std::cout<<"Persoana asta nu e pacient\n";
      std::cout<<e.what()<<"\n";
      return false;
   }
}

void afiseazaDate(Persoana* p) {
   p->afiseazaDate();
}

void updatePacient(Persoana* persoane[],int nrPersoane,int index,int prioritate) {
   int aux = 0;
   for (int i = 0;i < nrPersoane;i++) {
      Pacient* pacient = dynamic_cast<Pacient*>(persoane[i]);
      if (pacient != nullptr) {
         aux++;
         if (aux == index) {
            pacient->setPrioritate(prioritate);
            std::cout<<"Pacientul a fost updatat cu succes\n";
            pacient->afiseazaDate();
            return;
         }
      }
   }

   std::cout<<"Nu am gasit pacient sa updatam\n";
}

void stergeElement(Persoana* persoane[],int& nrPersoane,int index) {
   if (index < 0 || index > nrPersoane - 1) {
      std::cout<<"Index invalid\n";
      return;
   }
   delete persoane[index];
   for (int i = index;i < nrPersoane - 1;i++)
      persoane[i] = persoane[i + 1];
   persoane[nrPersoane - 1] = nullptr;
   nrPersoane--;
}

int main(){
  // Persoana p; Persoana este clasa abstarcta si nu poate fi instantiata (eroare de compilare)


  Persoana* persoane[50];
  std::string instructiune;
  std::getline(cin,instructiune);

   int nrPersoane = 0;
   while (true) {
      if (instructiune == "stop")
         break;

      if (instructiune == "introduce angajat") {
        persoane[nrPersoane] = new Angajat();
        cin>>*static_cast<Angajat*>(persoane[nrPersoane]);
         nrPersoane++;
      }
      else if (instructiune == "introduce doctor") {
         persoane[nrPersoane] = new Doctor();
         cin>>*static_cast<Doctor*>(persoane[nrPersoane]);
         nrPersoane++;
      }
      else if (instructiune == "introduce pacient") {
         persoane[nrPersoane] = new Pacient();
         cin>>*static_cast<Pacient*>(persoane[nrPersoane]);
         nrPersoane++;
      }
      else if (instructiune == "afiseaza date") {
         std::cout<<"introdu index-ul Persoanei care vrei sa fie afisata\n";
         int index;
         cin>>index;
         if (index < nrPersoane)
            afiseazaDate(persoane[index]);
      }
      else if (instructiune == "update pacient") {
         std::cout<<"Introdu index-ul pacientului, noua prioritate";
         int index, prioritate;
         cin>>index>>prioritate;
         updatePacient(persoane,nrPersoane,index,prioritate);
      }
      else if (instructiune == "sterge element") {
         std::cout<<"Introdu index-ul persoanei sterse\n";
         int index;
         cin>>index;
         stergeElement(persoane,nrPersoane,index);
      }
      else if (instructiune == "afiseaza array") {
         for (int i = 0;i< nrPersoane;i++)
            afiseazaDate(persoane[i]);
      }
      else {
         std::cout<<"Instructiune gresita\n";
      }
      std::getline(cin,instructiune);
   }

   for (int i = 0;i < nrPersoane;i++) {
      bool gasit = incercareGasireDoctor(*persoane[i],nrPersoane,persoane);
      if (!gasit)
         std::cout<<"pentru pacientul "<<*persoane[i]->getNume()<<" nu am gasit doctor disponibil\n";
   }

   // demonstratie ordine destructori
   Doctor d;
   Persoana* pers = &d;
   // se distruge in ordine: doctor, angajat, persoana, DataCalendaristica
  // d.pretConsultatie; eroare de compilare tipul pretConsultatie este protected

   for (int i = 0;i < nrPersoane;i++)
      delete persoane[i];
}