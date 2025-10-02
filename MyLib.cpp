#include "MyLib.h"
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <random>



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
