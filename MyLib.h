#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using std::cout;
using std::string;
using std::vector;
using std::accumulate;
using std::cout;
using std::cin;
using std::endl;

class Studentas {
    int a
    string vardas;
    string pavarde;
    vector<int>paz;
    int egzaminas;
    double rezultatas;
public:
    Studentas();
    Studentas(string A, string B, vector<int> C, int D);
    void rez();
    ~Studentas();
    void output();
    friend std::ostream& operator<<(std::ostream& os, const Studentas& obj);
    friend std::istream& operator>>(std::istream& is, Studentas& obj);
};
