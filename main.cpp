
#include "MyLib.h"

int main()
{
    vector<Studentas> grupe;
    for (int i = 0; i < 2; i++)
    {
        Studentas Test;
        //std::cin >> Test;
        grupe.push_back(Test);
    }
    for (auto& Z : grupe) cout << Z;
}
