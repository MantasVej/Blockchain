# Blockchain

## v0.1

**Naudojimo instrukcija**
1. Paleidus programą atsiveria terminalo langas.
2. Reikia pasirinkti ar generuoti naują transakcijų pool'ą, ar transakcijas nuskaityti iš failo.
3. Norint generuoti naują transakcijų pool'ą įvedamas 1, priešingu atveju - 0, po to įvedamas transakcijų failo pavadinimas.
4. Prieš kuriant transakcijas reikia pasirinkti ar vartotojus nuskaityti iš failo, ar generuoti naujus vartotojus.
5. Norint generuoti naujus vartotojus įvedamas 1, po to vartotojų ir transakcijų skaičius, priešingu atveju - 0, po to įvedamas vartotojų failo pavadinimas ir transakcijų skaičius.
6. Tuomet pasirenkama ar kurti naują blokų grandinę (blockchain'ą), įvedamas 1, priešingu atveju - 0, programos darbas baigiamas.
7. Sukurus naują blokų grandinę, sukuriamas 1 blokas (genesis block), kuriame talpinama iki 100 transakcijų.
8. Tolimesnis programos darbas priklauso nuo vartotojo įvesties:

    1 - pridėti naują bloką
  
    2 - tęsti blokų granbdinę kol transakcijų pool'e yra transakcijų
  
    3 - spausdinti informaciją apie bloką
  
    4 - spausdinti informaciją apie transakciją
  
    0 - baigti programos darbą
    
## v0.2
**Naudojimo instrukcija**

Tas pats kaip ir versijoje **v0.1**

**Pakeitimai**
1. Merkle medžio implementacija hash'uojant transakcijas.
2. Vartotjų balanso tikrinimas.
3. Patobulinta blokų kasimo (mining) strategija.
