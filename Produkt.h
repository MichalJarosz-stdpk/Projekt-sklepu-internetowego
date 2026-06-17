#ifndef PRODUKT_H
#define PRODUKT_H

#include <string>

class Produkt {
private:
    std::string nazwa;
    double cena;
    int ilosc;

public:
    Produkt(std::string n = "", double c = 0.0, int i = 0);
    
    std::string getNazwa() const { return nazwa; }
    double getCena() const { return cena; }
    int getIlosc() const { return ilosc; }
    
    void setIlosc(int nowaIlosc) { ilosc = nowaIlosc; }
    void dodajIlosc(int ile);
    bool zdejmijZStanu(int ile);
};

#endif