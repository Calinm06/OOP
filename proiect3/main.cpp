#include <iostream>

#include "Angajat.h"
#include "DataCalendaristica.h"
#include "Doctor.h"
#include "Pacient.h"
#include "Persoana.h"
#include <fstream>
#include <string>
#include <vector>

#include "Logger.h"
#include "Programare.h"
#include "AbstractFactory.h"

using namespace std;


bool incercareGasireDoctor(Persoana& p, const std::vector<Persoana*>& persoane) {
   try {
      Pacient& pacient = dynamic_cast<Pacient&>(p);
      const std::string& boala = pacient.getAfectiune();
      for (int i = 0; i < persoane.size(); i++) {
         Doctor* doctor = dynamic_cast<Doctor*>(persoane[i]);
         if (doctor != nullptr) {
            const std::string& specializare = doctor->getSpecializare();
            if (boala.empty() || specializare.empty())
               continue;
            if (boala == specializare) {
               std::cout << "Pentru pacientul " << pacient.getNume() << " am gasit doctorul " << doctor->getNume() << "\n";
               return true;
            }

         }
      }
      return false;
   }
   catch (std::bad_cast& e) {
      std::cout << "Persoana asta nu e pacient\n";
      std::cout << e.what() << "\n";
      return false;
   }
}

void afiseazaDate(Persoana* p) {
   p->afiseazaDate();
}

void updatePacient(std::vector<Persoana*>& persoane, int index, int prioritate) {//updateza al index-lea pacient
   int aux = 0;
   for (int i = 0; i < persoane.size(); i++) {
      Pacient* pacient = dynamic_cast<Pacient*>(persoane[i]);
      if (pacient != nullptr) {
         aux++;
         if (aux == index) {
            pacient->setPrioritate(prioritate);
            std::cout << "Pacientul a fost updatat cu succes\n";
            pacient->afiseazaDate();
            return;
         }
      }
   }

   std::cout << "Nu am gasit pacient sa updatam\n";
}

void stergeElement(std::vector<Persoana*>& persoane, int index) {
   if (index < 0 || index > persoane.size() - 1 || persoane.empty()) {
      std::cout << "Index invalid\n";
      return;
   }
   delete persoane[index];
   persoane.erase(persoane.begin() + index);
}

void demoTemplate() {
   //demo template-uri
   try {
      Pacient pacient(15, 3, 1990, {1,2,3,4,5,6,7,8,9,0,1,2,3}, "Ana Popescu","medicina");
      Doctor doctor(10, 5, 1980, {4,5,6,7,8,9,0,1,2,3,4,5,6}, "Ion Matei",
                   1, 8000, "medicina", "cardiologie", 200, 15);

      Programare<std::string, 120> p1(pacient, doctor, "consult", 45, "urgent");
      Programare<std::string, 120> p2(pacient, doctor, "control", 30, "periodic");
      Programare<std::string, 120> p3(pacient, doctor, "operatie", 90, "programata");

      p1.adaugaDetalii(std::string("prioritate maxima"));
      p1.adaugaDetalii(3);

      std::vector<Programare<std::string, 120>> lista = {p1, p2, p3};

      sorteaza(lista);

      for (const auto& p : lista)
         std::cout << "  Tip: " << p.getTipProgramare()<< " | Durata: " << p.getDurata() << "min\n";

      int c = numaraDupaTip(lista, std::string("consult"));
      std::cout << "Numar programari de tip 'consult': " << c << "\n";

      Programare<std::string, 120> urgenta(pacient, doctor, "urgenta", 15, "");
      std::cout << urgenta.getTipProgramare() << " | Durata: "
                << urgenta.getDurata() << "min\n";

      try {
         Programare<std::string, 120> gresita(pacient, doctor, "test", -5, "");
      } catch (const std::out_of_range& e) {
         std::cout << "Exceptie prinsa corect: " << e.what();
      }

   } catch (const std::exception& e) {
      std::cout << "Eroare demo: " << e.what() << "\n";
   }
}

void demoStackUnwinding() {
   // demo stack unwinding
   try {
      Angajat a1(1, 1, 2000, {1,2,3,4,5,6,7,8,9,0,1,2,3}, "Mihai",
                 1, 3000, "IT");

      Angajat a2(1, 1, 2000, {}, "", 2, 4000, "IT");
      cout<<a2;
   }
   catch (const ExceptieStringGol& e) {
      std::cout << "Prins: " << e.what() << "\n";
   }
   catch (const ExceptieCnpInvalid& e) {
      std::cout<<"Prins: "<<e.what()<<"\n";
   }
   catch (...) {
      std::cout << "Prins: exceptie necunoscuta\n";
   }
}

void demoAbstractFactory() {
   StandardFactory fabricaStandard;
   PremiumFactory fabricaPremium;

   DocumenteClient client(&fabricaStandard);

   std::vector<std::string> istoricIon = {"Hipertensiune", "Diabet tip 2"};
   client.proceseazaPacient("Ion Popescu", "Metformin", istoricIon);

   std::cout << "\n";

   client.setFabrica(&fabricaPremium);

   std::vector<std::string> istoricMaria = {"Astm bronsic", "Alergie la penicilina"};
   client.proceseazaPacient("Maria Ionescu", "Salbutamol", istoricMaria);
}

int main(){
  // Persoana p; Persoana este clasa abstarcta si nu poate fi instantiata (eroare de compilare)

  std::vector<Persoana*> persoane;
  std::string instructiune;
  std::getline(cin, instructiune);

   while (true) {
      if (instructiune == "stop")
         break;

      if (instructiune == "introduce angajat") {
        persoane.push_back(new Angajat());
        cin >> *static_cast<Angajat*>(persoane.back());
      }
      else if (instructiune == "introduce doctor") {
         persoane.push_back(new Doctor());
         cin >> *static_cast<Doctor*>(persoane.back());
      }
      else if (instructiune == "introduce pacient") {
         persoane.push_back(new Pacient());
         cin >> *static_cast<Pacient*>(persoane.back());
      }
      else if (instructiune == "afiseaza date") {
         std::cout << "introdu index-ul Persoanei care vrei sa fie afisata\n";
         int index;
         cin >> index;
         cin.ignore();
         if (index < persoane.size())
            afiseazaDate(persoane[index]);
      }
      else if (instructiune == "update pacient") {
         std::cout << "Introdu index-ul pacientului, noua prioritate";
         int index, prioritate;
         cin >> index >> prioritate;
         cin.ignore();
         updatePacient(persoane, index, prioritate);
      }
      else if (instructiune == "sterge element") {
         std::cout << "Introdu index-ul persoanei sterse\n";
         int index;
         cin >> index;
         cin.ignore();
         stergeElement(persoane, index);
      }
      else if (instructiune == "afiseaza array") {
         for (int i = 0; i < persoane.size(); i++)
            afiseazaDate(persoane[i]);
      }
      else if (instructiune == "filtreaza pacienti") {// raman doar pacientii
         vector<Persoana*>aux(persoane.size());
         auto itr = std::copy_if(persoane.begin(),persoane.end(),aux.begin(),[](Persoana* pers) {
            Pacient* p = dynamic_cast<Pacient *>(pers);
            return p != nullptr;
         });
         for (auto* p : persoane) {
            if (dynamic_cast<Pacient*>(p) == nullptr)
               delete p;
         }
         aux.resize(std::distance(aux.begin(), itr));
         persoane = aux;
      }
      else if (instructiune == "sorteaza") { // sorteaza dupa nume
         sort(persoane.begin(),persoane.end(),[](const Persoana* a,const Persoana* b) {
            return a->getNume() < b->getNume();// presupunem ca toti pacientii au nume, altfel ar da crash
         });
      }
      else if (instructiune == "afiseaza log") {
         Logger::getInstance().afiseazaLog();
      }
      else if (instructiune == "abstract factory") {
         IDocumentFactory* f = nullptr;
         cout<<"Introdu tipul familiei (standard/premium)\n";
         std::string tip;
         cin>>tip;
         cin.ignore();
         if (tip == "standard")
            f = new StandardFactory();
         else if (tip == "premium")
            f = new PremiumFactory();
         else
            cout<<"Instructiune invalida\n";

         if (f != nullptr) {
            DocumenteClient client(f);
            client.proceseazaPacient("Marcel","Aspacardin",{"Inima","Ficat"});
            delete f;
         }

      }
      else {
         std::cout << "Instructiune gresita\n";
      }
      std::getline(cin, instructiune);
   }

   for (int i = 0; i < persoane.size(); i++) {
      if (dynamic_cast<Pacient*>(persoane[i]) != nullptr) {
         try {
            bool gasit = incercareGasireDoctor(*persoane[i], persoane);
            if (!gasit)
               std::cout << "pentru pacientul " << persoane[i]->getNume() << " nu am gasit doctor disponibil\n";
         }
         catch (ExceptieStringGol) {
            std::cout<<"Pacientul nu are nume\n";
         }
      }

   }
  //
  //  // demonstratie ordine destructori
  //  Doctor d;
  //  Persoana* pers = &d;
  //  // se distruge in ordine: doctor, angajat, persoana, DataCalendaristica
  // // d.pretConsultatie; eroare de compilare tipul pretConsultatie este protected
  //
  for (int i = 0; i < persoane.size(); i++)
     delete persoane[i];

   //demoAbstractFactory();
   //demoStackUnwinding();
   //demoTemplate();
}