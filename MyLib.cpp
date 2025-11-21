#include <fstream> //
#include "MyLib.h"
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <random>
#include <chrono> 



Studentas::Studentas(std::string A, std::string B, std::vector<int> C, int D)
    : vardas(std::move(A)), pavarde(std::move(B)), paz(std::move(C)), egzaminas(D) {
    rez(); 
}

void Studentas::rez() {

    if (!paz.empty()) {
        double sum = std::accumulate(paz.begin(), paz.end(), 0.0);
        double hw  = sum / paz.size();
        rezultatas = 0.4 * hw + 0.6 * egzaminas;
    } else {
        rezultatas = 0.6 * egzaminas;
    }
}

void Studentas::skaiciuoti(bool pagalMediana) {
    double hw = pagalMediana ? mediana(paz) : vidurkis(paz);
    rezultatas = 0.4 * hw + 0.6 * egzaminas;
}

std::ostream& operator<<(std::ostream& os, const Studentas& obj) {
    os << std::left << std::setw(18) << obj.Pavarde()
       << std::setw(18) << obj.Vardas()
       << std::fixed << std::setprecision(2)
       << obj.Galutinis();
    return os;
}

std::istream& operator>>(std::istream& is, Studentas& obj) {
    obj.paz.clear();

    std::cout << "Iveskite varda: ";
    is >> obj.vardas;

    std::cout << "Iveskite pavarde: ";
    is >> obj.pavarde;

    std::cout << "Iveskite namu darbu pazymius (baigti 0): ";
    int n;
    while (is >> n && n != 0) {
        obj.paz.push_back(n);
    }

    std::cout << "Iveskite egzamino bala: ";
    is >> obj.egzaminas;


    obj.rez();

    std::cout << std::endl; 
    return is;
}



double vidurkis(const std::vector<int>& v) {
    if (v.empty()) return 0.0;
    double sum = std::accumulate(v.begin(), v.end(), 0.0);
    return sum / v.size();
}

double mediana(std::vector<int> v) {
    if (v.empty()) return 0.0;
    std::sort(v.begin(), v.end());
    size_t n = v.size();
    if (n % 2 == 1) return static_cast<double>(v[n/2]);
    return (v[n/2 - 1] + v[n/2]) / 2.0;
}



std::vector<Studentas> SkaitytiIsFailo(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("Nepavyko atidaryti failo: " + path);

    std::vector<Studentas> grupe;
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

        grupe.emplace_back(vardas, pavarde, paz, egz);
    }
    return grupe;
}



std::vector<Studentas> SugeneruotiStudentus(int N, int nd_kiek) {
    if (N <= 0 || nd_kiek <= 0) throw std::invalid_argument("N ir nd_kiek turi būti > 0");

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> d(1, 10);

    std::vector<Studentas> grupe;
    grupe.reserve(N);

    for (int i = 1; i <= N; ++i) {
        std::vector<int> nd(nd_kiek);
        for (int& x : nd) x = d(rng);
        int egz = d(rng);

        std::string v = "Vardas" + std::to_string(i);
        std::string p = "Pavarde" + std::to_string(i);

        Studentas s(v, p, std::move(nd), egz);

        grupe.emplace_back(std::move(s));
    }
    return grupe;
}

//
// Улучшенная функция генерации с таймером
void GeneruotiFaila(int kiekis, int nd_kiek) {
    if (kiekis <= 0 || nd_kiek <= 0) {
        std::cerr << "Kiekis ir ND kiek turi buti > 0\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> d(1, 10);

    std::string pavadinimas = "students" + std::to_string(kiekis) + ".txt";
    std::ofstream out(pavadinimas);

    if (!out) {
        std::cerr << "Nepavyko sukurti failo: " << pavadinimas << "\n";
        return;
    }

    // Заголовок
    out << "Pavarde Vardas";
    for (int j = 1; j <= nd_kiek; ++j) {
        out << " ND" << j;
    }
    out << " Egz\n";

    // Генерация студентов
    for (int i = 1; i <= kiekis; ++i) {
        out << "Pavarde" << i << " Vardas" << i;

        for (int j = 0; j < nd_kiek; ++j)
            out << " " << d(rng);

        out << " " << d(rng) << "\n";
    }

    out.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "✓ Sukurtas: " << pavadinimas 
              << " (laikas: " << std::fixed << std::setprecision(3) 
              << diff.count() << " s)\n";
}


// Функция разделения с детальным измерением времени
void PadalintiStudentus(const std::string& ivestiesFailas) {
    using namespace std::chrono;
    
    std::cout << "\n--- Padalinimas: " << ivestiesFailas << " ---\n";

    // 1. Чтение файла
    auto t1 = high_resolution_clock::now();
    
    std::vector<Studentas> visi;
    try {
        visi = SkaitytiIsFailo(ivestiesFailas);
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return;
    }

    auto t2 = high_resolution_clock::now();
    duration<double> skaitymoLaikas = t2 - t1;

    if (visi.empty()) {
        std::cerr << "Failas tuščias!\n";
        return;
    }

    // 2. Разделение студентов
    auto t3 = high_resolution_clock::now();

    std::vector<Studentas> kietiakiai;
    std::vector<Studentas> vargsiukai;
    
    kietiakiai.reserve(visi.size() / 2);
    vargsiukai.reserve(visi.size() / 2);

    for (const auto& s : visi) {
        if (s.Galutinis() >= 5.0) {
            kietiakiai.push_back(s);
        } else {
            vargsiukai.push_back(s);
        }
    }

    auto t4 = high_resolution_clock::now();
    duration<double> rusiavimoLaikas = t4 - t3;

    // 3. Запись в файлы
    auto t5 = high_resolution_clock::now();

    // Создаем имена файлов
    size_t dotPos = ivestiesFailas.find_last_of('.');
    std::string base = (dotPos != std::string::npos) 
                       ? ivestiesFailas.substr(0, dotPos) 
                       : ivestiesFailas;

    std::string kietiFail = base + "_kietiakiai.txt";
    std::string vargFail = base + "_vargsiukai.txt";

    // Записываем kietiakiai
    std::ofstream outKieti(kietiFail);
    if (outKieti) {
        outKieti << std::left << std::setw(18) << "Pavarde" 
                 << std::setw(18) << "Vardas" 
                 << "Galutinis\n";
        outKieti << std::string(54, '-') << "\n";
        
        for (const auto& s : kietiakiai) {
            outKieti << s << "\n";
        }
        outKieti.close();
    }

    // Записываем vargsiukai
    std::ofstream outVarg(vargFail);
    if (outVarg) {
        outVarg << std::left << std::setw(18) << "Pavarde" 
                << std::setw(18) << "Vardas" 
                << "Galutinis\n";
        outVarg << std::string(54, '-') << "\n";
        
        for (const auto& s : vargsiukai) {
            outVarg << s << "\n";
        }
        outVarg.close();
    }

    auto t6 = high_resolution_clock::now();
    duration<double> rasymoLaikas = t6 - t5;
    duration<double> bendrasLaikas = t6 - t1;

    // Выводим статистику
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "  Nuskaitymas:     " << skaitymoLaikas.count() << " s\n";
    std::cout << "  Rusiavimas:      " << rusiavimoLaikas.count() << " s\n";
    std::cout << "  Rasymas:         " << rasymoLaikas.count() << " s\n";
    std::cout << "  BENDRAS LAIKAS:  " << bendrasLaikas.count() << " s\n";
    std::cout << "  Kietiakiai:      " << kietiakiai.size() << " -> " << kietiFail << "\n";
    std::cout << "  Vargsiukai:      " << vargsiukai.size() << " -> " << vargFail << "\n\n";
}



