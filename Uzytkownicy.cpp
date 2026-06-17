#include "Uzytkownicy.h"
#include <iostream>

Uzytkownik::Uzytkownik(std::string l, std::string h, std::string r) : login(l), haslo(h), rola(r) {}

Klient::Klient(std::string l, std::string h) : Uzytkownik(l, h, "klient") {}

void Klient::wyswietlMenu() {
    std::cout << "\n--- MENU KLIENTA ---\n";
    std::cout << "1. Wyswietl produkty\n";
    std::cout << "2. Zloz zamowienie (koszyk)\n";
    std::cout << "3. Sprawdz historie transakcji\n";
    std::cout << "4. Wyloguj\n";
    std::cout << "Wybor: ";
}

Admin::Admin(std::string l, std::string h) : Uzytkownik(l, h, "admin") {}

void Admin::wyswietlMenu() {
    std::cout << "\n--- MENU ADMINISTRATORA ---\n";
    std::cout << "1. Wyswietl produkty\n";
    std::cout << "2. Dodaj nowy produkt\n";
    std::cout << "3. Usun produkt\n";
    std::cout << "4. Zamow dostawe (zwieksz ilosc)\n";
    std::cout << "5. Wyloguj\n";
    std::cout << "Wybor: ";
}