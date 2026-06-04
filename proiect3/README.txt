Proiectul este o aplicație consolă scrisă în C++ care modelează sistemul de management al unei clinici medicale, gestionând evidența pacienților și a personalului (angajați și doctori).

La baza arhitecturii stă o ierarhie de clase pe 3 niveluri (relația is-a): clasa abstractă de bază Persoana, din care derivă clasele Pacient și Angajat, cea din urmă fiind extinsă de clasa Doctor.

De asemenea, aplicația implementează relația de compunere (has-a) prin includerea unui obiect de tip DataCalendaristica în clasa Persoana. 

Din punct de vedere funcțional, programul oferă un meniu interactiv (CRUD) ce permite:Adăugarea de angajați, doctori și pacienți.Stocarea acestora într-o colecție polimorfică (tablou de pointeri la clasa de bază Persoana).  Afișarea tuturor înregistrărilor folosind polimorfismul la runtime (late binding).  Actualizarea detaliilor pacienților și ștergerea înregistrărilor.

Asocierea logică la finalul programului: căutarea automată a unui doctor disponibil a cărui specializare se potrivește cu afecțiunea fiecărui pacient (funcționalitate realizată prin downcasting sigur cu dynamic_cast).  