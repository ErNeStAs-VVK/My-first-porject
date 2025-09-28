#include "MyLib.h"

Studentas::Studentas() {
    vardas = "Testas";
    pavarde = "TestasTestas";
    paz = { 1,5,8,7,7,4,8,9};
    egzaminas = 10;
    rez();
}
Studentas::Studentas(string A, string B, vector<int> C, int D) {
    vardas = A;
    pavarde = B;
    paz = C;
    egzaminas = D;
    rez();
}
void Studentas::rez() {
    rezultatas = accumulate(paz.begin(), paz.end(), 0.) / paz.size() * 0.4 + egzaminas * 0.6;
}
Studentas::~Studentas() {
    vardas.clear();
    pavarde.clear();
    paz.clear();
    egzaminas = 0;
    rezultatas = 0;
}
void Studentas::output() {
    cout << vardas << " | " << pavarde << " | " << rezultatas << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Studentas& obj) {
    os << "| " << obj.vardas << " | " << obj.pavarde << " | " << obj.rezultatas << " |" << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Studentas& obj) {
    is >> obj.vardas >> obj.pavarde;
    int n;
    for (int i = 0; i < 5; i++)
    {
        is >> n;
        obj.paz.push_back(n);
    }
    is >> obj.egzaminas;
    obj.rez();
    return is;
}
