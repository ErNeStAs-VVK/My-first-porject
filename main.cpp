#include "MyLib.h"
#include <iostream>
#include <vector>
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

        std::cout << "Pasirinkite ivedimo buda:\n"
                  << "1 - Ivesti ranka (per klaviatura)\n"
                  << "2 - Sugeneruoti atsitiktinai\n"
                  << "3 - Nuskaityti is failo (kursiokai.txt)\n"
                  << "Jusu pasirinkimas: ";

        int mode = 0; 
        if (!(std::cin >> mode)) return 1;

        if (mode == 1) {
            int kiek = 0;
            std::cout << "Kiek studentu norite ivesti? ";
            std::cin >> kiek;
            grupe.reserve(std::max(0, kiek));
            for (int i = 0; i < kiek; ++i) {
                Studentas s;
                std::cin >> s; 
                grupe.push_back(std::move(s));
            }
        } else if (mode == 2) {
            int N, nd_kiek;
            std::cout << "Kiek studentu generuoti? ";
            std::cin >> N;
            std::cout << "Kiek namu darbu (ND) kiekvienam? ";
            std::cin >> nd_kiek;
            grupe = SugeneruotiStudentus(N, nd_kiek);
        } else if (mode == 3) {
            grupe = SkaitytiIsFailo("kursiokai.txt");
        } else {
            std::cerr << "Nezinomas pasirinkimas.\n";
            return 1;
        }

        if (grupe.empty()) {
            std::cout << "Grupe tuscia.\n";
            return 0;
        }


        std::cout << "Skaiciuoti pagal (1) Vidurki ar (2) Mediana? ";
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
