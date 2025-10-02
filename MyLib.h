#pragma once
#include <iostream>
#include <string>
#include <vector>


class Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;   
    int egzaminas = 0;      
    double rezultatas = 0.0;

public:

    Studentas() = default;
    Studentas(const Studentas&) = default;
    Studentas& operator=(const Studentas&) = default;
    ~Studentas() = default;

    Studentas(std::string A, std::string B, std::vector<int> C, int D);


    void skaiciuoti(bool pagalMediana); 
    void rez(); 


    friend std::ostream& operator<<(std::ostream& os, const Studentas& obj);
    friend std::istream& operator>>(std::istream& is, Studentas& obj);

    // Getteriai
    const std::string& Vardas()   const { return vardas; }
    const std::string& Pavarde()  const { return pavarde; }
    const std::vector<int>& Paz() const { return paz; }
    int Egz() const { return egzaminas; }
    double Galutinis() const { return rezultatas; }
};


double vidurkis(const std::vector<int>& v);
double mediana(std::vector<int> v);


std::vector<Studentas> SkaitytiIsFailo(const std::string& path);


std::vector<Studentas> SugeneruotiStudentus(int N, int nd_kiek);
