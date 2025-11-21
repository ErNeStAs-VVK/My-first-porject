Studentų analizės programa v1.0
Kas nauja v1.0?
 Palaikomi 3 konteinerių tipai: vector, list, deque
 2 rūšiavimo strategijos:

Strategija 1: Sukuria 2 naujus failus (kietiakiai + vargšiukai), pagrindinis failas lieka nepakeistas
Strategija 2: Sukuria 1 failą (vargšiukai), o pagrindinis failas perrašomas (lieka tik kietiakiai)

 Lanksčus vartotojo pasirinkimas: konteineris + strategija
 Detalūs laiko matavimai kiekvienam etapui


 Kompiliavimas
Linux/Mac:
1)      g++ -std=c++17 -O2 -Wall main.cpp MyLib.cpp -o programa
2)      clang++ -std=c++17 main.cpp MyLib.cpp -o main

  Windows:
  g++ -std=c++17 -O2 -Wall main.cpp MyLib.cpp -o programa.exe


Naudojimas
Režimas 4: Strategijų testavimas
Pasirinkite režimą:
1 - Įvesti rankiniu būdu
2 - Sugeneruoti atsitiktinai
3 - Nuskaityti iš failo (kursiokai.txt)
4 - Generuoti failus ir testuoti strategijas (v1.0)
Jūsų pasirinkimas: 


1 žingsnis: Pasirinkti konteinerį
Pasirinkite konteinerį:
1 - vector
2 - list
3 - deque
Pasirinkimas: 

2 žingsnis: Nurodyti dydį
Kiek studentų generuoti? 1000
Kiek ND kiekvienam? 


3 žingsnis: Pasirinkti strategiją
Pasirinkite strategiją:
1 - Strategija 1: Kopijuoti į 2 naujus failus (kietiakiai + vargšiukai)
2 - Strategija 2: Perkelti vargšiukus ir ištrinti iš pagrindinio
Pasirinkimas: 


Strategijų palyginimas
Strategija 1: Kopijavimas į 2 naujus failus
Kaip veikia:

Nuskaito students1000.txt
Sukuria 2 naujus failus:

students1000_kietiakiai.txt (galutinis ≥ 5.0)
students1000_vargsiukai.txt (galutinis < 5.0)


Pagrindinis failas lieka nepakeistas

Rezultatas:
students1000.txt              (1000 studentų) ← nepakeistas
students1000_kietiakiai.txt   (503 studentai)
students1000_vargsiukai.txt   (497 studentai)
Privalumai:

✅ Saugus (originalas išsaugotas)
✅ Aiškus rezultatas (3 failai)

Trūkumai:

❌ Dvigubas atminties naudojimas
❌ Daugiau disko vietos


Strategija 2: Perkėlimas su ištrinimu
Kaip veikia:

Nuskaito students1000.txt
Perkelia vargšiukus į students1000_vargsiukai.txt
Perrašo pagrindinį failą (lieka tik kietiakiai)

Rezultatas:
students1000.txt              (503 studentai) ← PERRAŠYTAS! tik kietiakiai
students1000_vargsiukai.txt   (497 studentai)
Privalumai:

Privalumai:
 Efektyvesnis atminties naudojimas
 Mažiau disko vietos

Trūkumai:
 Originalas prarandamas
 erase() gali būti lėtas (ypač vector)

VECTOR:
Pavyzdžio išvestis
Strategija 1 (vector, 1000 studentų):
=== STRATEGIJA 1 (vector) ===
Failas: students1000.txt
Aprašymas: Kopijuojami studentai į 2 naujus failus

--- Rezultatai ---
  Nuskaitymas:     0.0023 s
  Rusiavimas:      0.0015 s
  Rasymas:         0.0018 s
  BENDRAS LAIKAS:  0.0056 s

--- Sukurti failai ---
  Pradinis failas:    students1000.txt (1000 studentų)
  Kietiakiai failas:  students1000_kietiakiai.txt (503 studentų)
  Vargšiukai failas:  students1000_vargsiukai.txt (497 studentų)


LIST:
Strategija 2 (list, 1000 studentų):
=== STRATEGIJA 2 (list) ===
Failas: students1000.txt
Aprašymas: Vargšiukai perkeliami į atskirą failą ir ištrinami iš pagrindinio

--- Rezultatai ---
  Nuskaitymas:     0.0025 s
  Rusiavimas:      0.0008 s
  Rasymas:         0.0019 s
  BENDRAS LAIKAS:  0.0052 s

--- Failai po padalinimo ---
  Pradinis failas:    students1000.txt (503 studentų - tik kietiakiai) 
  Vargšiukai failas:  students1000_vargsiukai.txt (497 studentų)
  Iš viso buvo:       1000 studentų


DEQUE:
  === STRATEGIJA 1 (deque) ===
Failas: students1000.txt
Aprašymas: Kopijuojami studentai į 2 naujus failus

--- Rezultatai ---
  Nuskaitymas:     0.0036 s
  Rusiavimas:      0.0002 s
  Rasymas:         0.0006 s
  BENDRAS LAIKAS:  0.0044 s

--- Sukurti failai ---
  Pradinis failas:    students1000.txt (1000 studentų)
  Kietiakiai failas:  students1000_kietiakiai.txt (609 studentų)
  Vargšiukai failas:  students1000_vargsiukai.txt (391 studentų)



Dydis        Konteineris        Strategija 1        Strategija 2
1,000          vector             ~0.005s             ~0.005s 
1,000            list             ~0.006s             ~0.005s
1,000           deque             ~0.005s             ~0.005s 
10,000          vector            ~0.05s              ~0.1s 
10,000          list              ~0.06s              ~0.05s 
10,000          deque             ~0.05s              ~0.07s 
100,000         vector            ~0.5s               ~2s 
100,000          list             ~0.6s               ~0.5s
100,000         deque             ~0.5s               ~1s 
1,000,000      vector              ~5s                ~60s 
1,000,000       list               ~6s                ~5s 
1,000,000      deque               ~5s                ~20s 
10,000,000    vector              ~50s                ~600s
10,000,000      list              ~60s                ~50s
10,000,000     deque              ~50                 ~200s





Strategija 2 pakeičia pagrindinį failą! Jei norite išsaugoti originalą, naudokite Strategija 1.
Vector + Strategija 2 tampa labai lėtas su dideliais failais (>100k).
List naudoja daugiau atminties nei vector, bet erase() yra daug greitesnis.

Testavimo patarimai

Pirma išbandykite mažu failu (1000 studentų)
Palyginkite laikus skirtingiems konteineriams
Dideliems failams (>100k) naudokite list + Strategija 2
Jei svarbu išsaugoti originalą - visada Strategija 1





