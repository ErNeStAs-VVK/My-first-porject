#include <iostream>
#include <stdexcept>


int main() {
    try {
        int capacity = 4;
        int size = 0;
        int* nd = new int[capacity];

        std::cout << "Iveskite namu darbu pazymius (1..10), baigti 0: ";
        int x;
        while (std::cin >> x && x != 0) {
            if (x < 1 || x > 10) {
                std::cerr << "(Persp.) Balas turi buti 1..10, praleidziu\n";
                continue;
            }
            if (size == capacity) {

                int newCap = capacity * 2;
                int* tmp = new int[newCap];
                for (int i = 0; i < size; ++i) tmp[i] = nd[i];
                delete[] nd;
                nd = tmp;
                capacity = newCap;
            }
            nd[size++] = x;
        }

        std::cout << "Iveskite egzamino bala (1..10): ";
        int egz = 0; 
        std::cin >> egz;


        std::cout << "ND kiekis: " << size << ", egzaminas: " << egz << "\n";

        delete[] nd;
    } catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
