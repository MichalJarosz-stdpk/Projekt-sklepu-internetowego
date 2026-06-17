#include "Produkt.h"

Produkt::Produkt(std::string n, double c, int i) : nazwa(n), cena(c), ilosc(i) {}

bool Produkt::zdejmijZStanu(int ile) {
    if (ilosc >= ile) {
        ilosc -= ile;
        return true;
    }
    return false;
}

void Produkt::dodajIlosc(int ile) {
    if (ile > 0) {
        ilosc += ile;
    }
}