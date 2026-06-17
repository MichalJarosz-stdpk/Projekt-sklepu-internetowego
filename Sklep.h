#ifndef SKLEP_H
#define SKLEP_H

#include <vector>
#include "Produkt.h"
#include "Uzytkownicy.h"

class Sklep {
private:
    std::vector<Produkt> produkty;
    std::vector<Uzytkownik*> uzytkownicy;
    Uzytkownik* aktualnyUzytkownik;

    void wczytajProdukty();
    void zapiszProdukty();
    void wczytajUzytkownikow();

public:
    Sklep();
    ~Sklep();

    bool zaloguj();
    void uruchom();
    
    void wyswietlProdukty();
    void zlozZamowienie();
    void pokazHistorie();

    void dodajProdukt();
    void usunProdukt();
    void zamowDostawe();
};

#endif