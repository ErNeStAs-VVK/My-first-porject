Naujovės v0.2 versijoje

 **1. Galima generuoti itin didelius studentų failus**
Programa dabar leidžia generuoti failus su:
      - 100 tūkst.
      - 1 mln.
      - 10 mln. ir daugiau studentų įrašų.

**2. Galima pasirinkti namų darbų (ND) kiekį**
Vartotojas gali pats nurodyti, kiek namų darbų rezultatų generuoti kiekvienam studentui.

**3. Automatinis studentų rūšiavimas į dvi grupes**
Sugeneravus pirminį failą, programa automatiškai sukuria du naujus failus:
      - vargsiukai.txt — žemesni balai (blogi studentai)
      - kietiakai.txt — aukšti balai (geri studentai)

4. Matomas programos veikimo greitis
Programa parodo:
      - kiek laiko truko failų generavimas,
      - kiek laiko užtruko studentų padalinimas į grupes,
      - bendrą apdorojimo laiką.


5. **Konteinerių palyginimas**:
Programoje išbandžiau tris STL konteinerius studentų duomenų saugojimui: std::vector, std::deque ir std::list.

1.1 **std::vector pasirodė greičiausias.**
Jis naudoja vientisą atminties bloką, todėl:
    - greitai skaitomas nuosekliai,
    - efektyviai veikia std::sort,
    - mažesnės atminties sąnaudos.

1.2 **std::deque** veikė panašiai kaip vector – šiek tiek lėčiau (dėl sudėtingesnės vidinės struktūros), bet skirtumas nedidelis. std::sort taip pat veikia, nes yra atsitiktinės prieigos iteratoriai.

1.3 **std::list buvo aiškiai lėčiausias:**
    - kiekvienas elementas saugomas atskirame mazge,
    - daug dinaminių atminties paskyrimų,
    - prastas procesoriaus kešo panaudojimas,
    - reikėjo naudoti _list::sort_, nes _std::sort_ neveikia.
    - 
Testuojant su dideliais failais (šimtais tūkstančių ir milijonais įrašų), std::list veikimo laikas buvo kelis kartus blogesnis už std::vector, o std::deque nuo vector skyrėsi tik nežymiai.
