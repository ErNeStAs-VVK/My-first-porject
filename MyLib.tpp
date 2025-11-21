#pragma once
#include "MyLib.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <stdexcept>


template<typename Container>
Container SkaitytiIsFailoContainer(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Nepavyko atidaryti failo: " + path);

    Container grupe;
    std::string line;

    std::getline(in, line);

    while (std::getline(in, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);

        std::string pavarde, vardas;
        if (!(iss >> pavarde >> vardas)) continue;

        std::vector<int> paz;
        int x;
        while (iss >> x) paz.push_back(x);
        if (paz.empty()) continue;

        int egz = paz.back();
        paz.pop_back();

        grupe.push_back(Studentas(vardas, pavarde, paz, egz));
    }
    return grupe;
}


template<typename Container>
void RasytiIFaila(const std::string& filename, const Container& konteineris) {
    std::ofstream out(filename);
    if (!out) return;
    
    out << std::left << std::setw(18) << "Pavarde" 
        << std::setw(18) << "Vardas" 
        << "Galutinis\n";
    out << std::string(54, '-') << "\n";
    
    for (const auto& s : konteineris) {
        out << s << "\n";
    }
}


template<typename Container>
void PadalintiStudentusStrategija1(const std::string& ivestiesFailas, const std::string& containerName) {
    using namespace std::chrono;
    
    std::cout << "\n=== STRATEGIJA 1 (" << containerName << ") ===\n";
    std::cout << "Failas: " << ivestiesFailas << "\n";
    std::cout << "Aprašymas: Kopijuojami studentai į 2 naujus failus\n";

    
    auto t1 = high_resolution_clock::now();
    Container visi;
    try {
        visi = SkaitytiIsFailoContainer<Container>(ivestiesFailas);
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return;
    }
    auto t2 = high_resolution_clock::now();

    if (visi.empty()) {
        std::cerr << "Failas tuščias!\n";
        return;
    }

   
    auto t3 = high_resolution_clock::now();
    
    Container kietiakiai;
    Container vargsiukai;
    
    for (const auto& s : visi) {
        if (s.Galutinis() >= 5.0) {
            kietiakiai.push_back(s);
        } else {
            vargsiukai.push_back(s);
        }
    }
    
    auto t4 = high_resolution_clock::now();

   
    auto t5 = high_resolution_clock::now();
    
    size_t dotPos = ivestiesFailas.find_last_of('.');
    std::string base = (dotPos != std::string::npos) 
                       ? ivestiesFailas.substr(0, dotPos) 
                       : ivestiesFailas;

    std::string kietiFail = base + "_kietiakiai.txt";
    std::string vargFail = base + "_vargsiukai.txt";

    RasytiIFaila(kietiFail, kietiakiai);
    RasytiIFaila(vargFail, vargsiukai);
    
    auto t6 = high_resolution_clock::now();

  
    duration<double> skaitymoLaikas = t2 - t1;
    duration<double> rusiavimoLaikas = t4 - t3;
    duration<double> rasymoLaikas = t6 - t5;
    duration<double> bendrasLaikas = t6 - t1;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n--- Rezultatai ---\n";
    std::cout << "  Nuskaitymas:     " << skaitymoLaikas.count() << " s\n";
    std::cout << "  Rusiavimas:      " << rusiavimoLaikas.count() << " s\n";
    std::cout << "  Rasymas:         " << rasymoLaikas.count() << " s\n";
    std::cout << "  BENDRAS LAIKAS:  " << bendrasLaikas.count() << " s\n\n";
    std::cout << "--- Sukurti failai ---\n";
    std::cout << "  Pradinis failas:    " << ivestiesFailas << " (" << visi.size() << " studentų)\n";
    std::cout << "  Kietiakiai failas:  " << kietiFail << " (" << kietiakiai.size() << " studentų)\n";
    std::cout << "  Vargšiukai failas:  " << vargFail << " (" << vargsiukai.size() << " studentų)\n\n";
}


template<typename Container>
void PadalintiStudentusStrategija2(const std::string& ivestiesFailas, const std::string& containerName) {
    using namespace std::chrono;
    
    std::cout << "\n=== STRATEGIJA 2 (" << containerName << ") ===\n";
    std::cout << "Failas: " << ivestiesFailas << "\n";
    std::cout << "Aprašymas: Vargšiukai perkeliami į atskirą failą ir ištrinami iš pagrindinio\n";

 
    auto t1 = high_resolution_clock::now();
    Container kietiakiai; 
    try {
        kietiakiai = SkaitytiIsFailoContainer<Container>(ivestiesFailas);
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return;
    }
    auto t2 = high_resolution_clock::now();

    if (kietiakiai.empty()) {
        std::cerr << "Failas tuščias!\n";
        return;
    }

    size_t pradineKiekis = kietiakiai.size();

   
    auto t3 = high_resolution_clock::now();
    
    Container vargsiukai;
    
   
    auto it = kietiakiai.begin();
    while (it != kietiakiai.end()) {
        if (it->Galutinis() < 5.0) {
            vargsiukai.push_back(*it);
            it = kietiakiai.erase(it); 
        } else {
            ++it;
        }
    }
    
    auto t4 = high_resolution_clock::now();

   
    auto t5 = high_resolution_clock::now();
    
    size_t dotPos = ivestiesFailas.find_last_of('.');
    std::string base = (dotPos != std::string::npos) 
                       ? ivestiesFailas.substr(0, dotPos) 
                       : ivestiesFailas;

    std::string vargFail = base + "_vargsiukai.txt";

 
    RasytiIFaila(ivestiesFailas, kietiakiai);
    
 
    RasytiIFaila(vargFail, vargsiukai);
    
    auto t6 = high_resolution_clock::now();

   
    duration<double> skaitymoLaikas = t2 - t1;
    duration<double> rusiavimoLaikas = t4 - t3;
    duration<double> rasymoLaikas = t6 - t5;
    duration<double> bendrasLaikas = t6 - t1;

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "\n--- Rezultatai ---\n";
    std::cout << "  Nuskaitymas:     " << skaitymoLaikas.count() << " s\n";
    std::cout << "  Rusiavimas:      " << rusiavimoLaikas.count() << " s\n";
    std::cout << "  Rasymas:         " << rasymoLaikas.count() << " s\n";
    std::cout << "  BENDRAS LAIKAS:  " << bendrasLaikas.count() << " s\n\n";
    std::cout << "--- Failai po padalinimo ---\n";
    std::cout << "  Pradinis failas:    " << ivestiesFailas << " (" << kietiakiai.size() << " studentų - tik kietiakiai)\n";
    std::cout << "  Vargšiukai failas:  " << vargFail << " (" << vargsiukai.size() << " studentų)\n";
    std::cout << "  Iš viso buvo:       " << pradineKiekis << " studentų\n\n";
}
