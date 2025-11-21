#include "MyLib.h"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iomanip>

static void SpausdintiAntraste(bool pagalMediana) {
    std::cout << std::left
              << std::setw(18) << "Pavarde"
              << std::setw(18) << "Vardas"
              << std::setw(22) << (pagalMediana ? "Galutinis (Med.)" : "Galutinis (Vid.)")
              << "\n---------------------------------------------------------------\n";
}

static void AtnaujintiGalutinius(std::vector<Studentas>& grupe, bool pagalMediana) {
    for (auto& s : grupe) s.skaiciuoti(pagalMediana);
}

int main() {
    try {
        std::vector<Studentas> grupe;
        
        std::cout << "\n         STUDENTŲ ANALIZĖS PROGRAMA v1.0\n \n";
        
        std::cout << "Pasirinkite režimą:\n"
                  << "1 - Įvesti rankiniu būdu\n"
                  << "2 - Sugeneruoti atsitiktinai\n"
                  << "3 - Nuskaityti iš failo (kursiokai.txt)\n"
                  << "4 - Generuoti failus ir testuoti strategijas (v1.0)\n"
                  << "Jūsų pasirinkimas: ";
        
        int mode = 0; 
        if (!(std::cin >> mode)) return 1;
        
        if (mode == 1) {
            int kiek = 0;
            std::cout << "Kiek studentų norite įvesti? ";
            std::cin >> kiek;
            grupe.reserve(std::max(0, kiek));
            
            for (int i = 0; i < kiek; ++i) {
                Studentas s;
                std::cin >> s; 
                grupe.push_back(std::move(s));
            }
            
        } else if (mode == 2) {
            int N, nd_kiek;
            std::cout << "Kiek studentų generuoti? ";
            std::cin >> N;
            std::cout << "Kiek namų darbų (ND) kiekvienam? ";
            std::cin >> nd_kiek;
            grupe = SugeneruotiStudentus(N, nd_kiek);
            
        } else if (mode == 3) {
            grupe = SkaitytiIsFailo("kursiokai.txt");
            
        } else if (mode == 4) {

            std::cout << "\n  STRATEGIJŲ TESTAVIMAS \n \n";

            

            std::cout << "Pasirinkite konteinerį:\n"
                      << "1 - vector\n"
                      << "2 - list\n"
                      << "3 - deque\n"
                      << "Pasirinkimas: ";
            
            int containerChoice;
            std::cin >> containerChoice;
            
            int kiekis, nd_kiek;
            std::cout << "\nKiek studentų generuoti? ";
            std::cin >> kiekis;
            std::cout << "Kiek ND kiekvienam? ";
            std::cin >> nd_kiek;
            
            GeneruotiFaila(kiekis, nd_kiek);
            std::string failoPav = "students" + std::to_string(kiekis) + ".txt";

            std::cout << "\nPasirinkite strategiją:\n"
                      << "1 - Strategija 1: Kopijuoti į 2 naujus failus (kietiakiai + vargšiukai)\n"
                      << "2 - Strategija 2: Perkelti vargšiukus ir ištrinti iš pagrindinio\n"
                      << "Pasirinkimas: ";
            
            int strategija;
            std::cin >> strategija;
            
            std::cout << "\n";
            
            if (containerChoice == 1) {
                if (strategija == 1) {
                    PadalintiStudentusStrategija1<std::vector<Studentas>>(failoPav, "vector");
                } else {
                    PadalintiStudentusStrategija2<std::vector<Studentas>>(failoPav, "vector");
                }
            } else if (containerChoice == 2) {
                if (strategija == 1) {
                    PadalintiStudentusStrategija1<std::list<Studentas>>(failoPav, "list");
                } else {
                    PadalintiStudentusStrategija2<std::list<Studentas>>(failoPav, "list");
                }
            } else if (containerChoice == 3) {
                if (strategija == 1) {
                    PadalintiStudentusStrategija1<std::deque<Studentas>>(failoPav, "deque");
                } else {
                    PadalintiStudentusStrategija2<std::deque<Studentas>>(failoPav, "deque");
                }
            }
            
            return 0;
        }
        
        if (grupe.empty()) {
            std::cout << "Grupė tuščia.\n";
            return 0;
        }
        
        std::cout << "Skaičiuoti pagal (1) Vidurkį ar (2) Medianą? ";
        int m = 1; 
        std::cin >> m;
        bool pagalMediana = (m == 2);
        
        AtnaujintiGalutinius(grupe, pagalMediana);
        
        std::sort(grupe.begin(), grupe.end(),
                  [](const Studentas& a, const Studentas& b) {
                      if (a.Pavarde() == b.Pavarde()) return a.Vardas() < b.Vardas();
                      return a.Pavarde() < b.Pavarde();
                  });
        
        SpausdintiAntraste(pagalMediana);
        for (const auto& s : grupe) {
            std::cout << s << "\n"; 
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
