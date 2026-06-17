#include "Sklep.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

void wyczyscStrumien() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Sklep::Sklep() : aktualnyUzytkownik(nullptr) {
    produkty.push_back(Produkt("Jajko", 1.00, 10));
    produkty.push_back(Produkt("Mleko", 3.50, 20));
    produkty.push_back(Produkt("Chleb", 4.20, 15));

    wczytajProdukty();
    zapiszProdukty();
    wczytajUzytkownikow();
}

Sklep::~Sklep() {
    zapiszProdukty();
    for (auto u : uzytkownicy) {
        delete u;
    }
}

void Sklep::wczytajProdukty() {
    std::ifstream plik("baza_produktow.txt");
    if (!plik.is_open()) return;

    if (plik.peek() == std::ifstream::traits_type::eof()) {
        plik.close();
        return; 
    }

    std::string nazwa;
    double cena;
    int ilosc;
    
    std::vector<Produkt> wczytane;
    while (plik >> nazwa >> cena >> ilosc) {
        if (nazwa.find("02332") == std::string::npos && cena < 1000000 && cena > 0) {
            wczytane.push_back(Produkt(nazwa, cena, ilosc));
        }
    }
    plik.close();

    if (!wczytane.empty()) {
        produkty = wczytane;
    }
}

void Sklep::zapiszProdukty() {
    std::ofstream plik("baza_produktow.txt", std::ios::trunc); 
    if (!plik.is_open()) return;
    
    for (const auto& p : produkty) {
        plik << p.getNazwa() << " " << p.getCena() << " " << p.getIlosc() << "\n";
    }
    plik.close();
}

void Sklep::wczytajUzytkownikow() {
    std::ifstream plik("uzytkownicy.txt");
    if (!plik.is_open()) {
        uzytkownicy.push_back(new Admin("admin", "admin123"));
        uzytkownicy.push_back(new Klient("jan", "haslo"));
        return;
    }
    std::string log, has, rol;
    while (plik >> log >> has >> rol) {
        if (rol == "admin") uzytkownicy.push_back(new Admin(log, has));
        else uzytkownicy.push_back(new Klient(log, has));
    }
    plik.close();
}

bool Sklep::zaloguj() {
    std::string log, has;
    std::cout << "--- LOGOWANIE ---\nLogin: ";
    std::cin >> log;
    std::cout << "Haslo: ";
    std::cin >> has;

    for (auto u : uzytkownicy) {
        if (u->getLogin() == log && u->getHaslo() == has) {
            aktualnyUzytkownik = u;
            std::cout << "Zalogowano pomyslnie jako " << u->getLogin() << " (" << u->getRola() << ")\n";
            return true;
        }
    }
    std::cout << "Bledny login lub haslo!\n";
    return false;
}

void Sklep::wyswietlProdukty() {
    zapiszProdukty();
    std::cout << "\n--- ASORTYMENT SKLEPU ---\n";
    if (produkty.empty()) {
        std::cout << "Brak produktow w sklepie.\n";
        return;
    }
    for (size_t i = 0; i < produkty.size(); ++i) {
        std::cout << i + 1 << ". " << produkty[i].getNazwa() 
                  << " | Cena: " << produkty[i].getCena() << " zl"
                  << " | Dostepna ilosc: " << produkty[i].getIlosc() << "\n";
    }
}

void Sklep::zlozZamowienie() {
    wyswietlProdukty();
    if (produkty.empty()) return;

    std::vector<std::pair<int, int>> koszyk;
    char dalej = 't';

    while (dalej == 't' || dalej == 'T') {
        int nr, ile;
        std::cout << "Podaj numer produktu, ktory chcesz kupic: ";
        if (!(std::cin >> nr)) {
            std::cout << "Niepoprawny znak! Wpisz liczbe.\n";
            wyczyscStrumien();
            continue;
        }
        
        if (nr < 1 || nr > (int)produkty.size()) {
            std::cout << "Niepoprawny numer produktu.\n";
            continue;
        }
        
        std::cout << "Podaj ilosc: ";
        if (!(std::cin >> ile) || ile <= 0) {
            std::cout << "Niepoprawna ilosc!\n";
            wyczyscStrumien();
            continue;
        }

        if (produkty[nr - 1].getIlosc() < ile) {
            std::cout << "Niewystarczajaca ilosc na stanie! Dostepne: " << produkty[nr - 1].getIlosc() << "\n";
        } else {
            koszyk.push_back({nr - 1, ile});
            std::cout << "Dodano do koszyka.\n";
        }
        std::cout << "Czy chcesz dodac kolejny produkt? (t/n): ";
        std::cin >> dalej;
    }

    if (koszyk.empty()) return;

    double suma = 0;
    std::ofstream historia("historia.txt", std::ios::app);
    historia << "Uzytkownik: " << aktualnyUzytkownik->getLogin() << "\nZakupy:\n";

    for (auto& para : koszyk) {
        int idx = para.first;
        int ile = para.second;
        if (produkty[idx].zdejmijZStanu(ile)) {
            double koszt = produkty[idx].getCena() * ile;
            suma += koszt;
            historia << "- " << produkty[idx].getNazwa() << " x" << ile << " (" << koszt << " zl)\n";
        }
    }
    historia << "Suma: " << suma << " zl\n-------------------------\n";
    historia.close();

    std::cout << "Zamowienie zrealizowane! Koszt calkowity: " << suma << " zl\n";
    zapiszProdukty();
}

void Sklep::pokazHistorie() {
    std::ifstream plik("historia.txt");
    if (!plik.is_open()) {
        std::cout << "Brak historii transakcji.\n";
        return;
    }
    std::cout << "\n--- HISTORIA TRANSAKCJI ---\n";
    std::string linia;
    while (std::getline(plik, linia)) {
        std::cout << linia << "\n";
    }
    plik.close();
}

void Sklep::dodajProdukt() {
    std::string nazwa;
    double cena;
    int ilosc;
    std::cout << "Podaj nazwe nowego produktu (bez spacji): ";
    std::cin >> nazwa;
    
    std::cout << "Podaj cene: ";
    if (!(std::cin >> cena)) {
        std::cout << "Blad: Cena musi byc liczba!\n";
        wyczyscStrumien();
        return;
    }
    
    std::cout << "Podaj ilosc poczatkowa: ";
    if (!(std::cin >> ilosc)) {
        std::cout << "Blad: Ilosc musi byc liczba calkowita!\n";
        wyczyscStrumien();
        return;
    }

    produkty.push_back(Produkt(nazwa, cena, ilosc));
    std::cout << "Produkt zostal dodany.\n";
    zapiszProdukty();
    wyczyscStrumien();
}

void Sklep::usunProdukt() {
    wyswietlProdukty();
    if (produkty.empty()) return;
    int nr;
    std::cout << "Podaj numer produktu do usuniecia: ";
    if (!(std::cin >> nr)) {
        std::cout << "Blad: Podaj liczbe!\n";
        wyczyscStrumien();
        return;
    }
    if (nr < 1 || nr > (int)produkty.size()) {
        std::cout << "Niepoprawny numer.\n";
        return;
    }
    produkty.erase(produkty.begin() + (nr - 1));
    std::cout << "Produkt zostal usuniety.\n";
    zapiszProdukty();
}

void Sklep::zamowDostawe() {
    wyswietlProdukty();
    if (produkty.empty()) return;
    int nr, ile;
    std::cout << "Podaj numer produktu do dostawy: ";
    if (!(std::cin >> nr)) {
        std::cout << "Blad: Podaj liczbe!\n";
        wyczyscStrumien();
        return;
    }
    if (nr < 1 || nr > (int)produkty.size()) {
        std::cout << "Niepoprawny numer.\n";
        return;
    }
    std::cout << "Ile sztuk dostarczyc?: ";
    if (!(std::cin >> ile)) {
        std::cout << "Blad: Podaj liczbe!\n";
        wyczyscStrumien();
        return;
    }
    produkty[nr - 1].dodajIlosc(ile);
    std::cout << "Dostawa przyjeta. Nowy stan produktu: " << produkty[nr - 1].getIlosc() << "\n";
    zapiszProdukty();
}

void Sklep::uruchom() {
    while (true) {
        if (!aktualnyUzytkownik) {
            std::cout << "\n1. Zaloguj sie\n2. Wyjdz z programu\nWybor: ";
            int w;
            if (!(std::cin >> w)) {
                std::cout << "Wprowadzono niepoprawny znak!\n";
                wyczyscStrumien();
                continue;
            }
            if (w == 2) break;
            if (w == 1) zaloguj();
            continue;
        }

        aktualnyUzytkownik->wyswietlMenu();
        int wybor;
        if (!(std::cin >> wybor)) {
            std::cout << "Wprowadzono niepoprawny wybor menu!\n";
            wyczyscStrumien();
            continue;
        }

        if (aktualnyUzytkownik->getRola() == "klient") {
            if (wybor == 1) wyswietlProdukty();
            else if (wybor == 2) zlozZamowienie();
            else if (wybor == 3) pokazHistorie();
            else if (wybor == 4) aktualnyUzytkownik = nullptr;
            else std::cout << "Niepoprawna opcja menu.\n";
        } 
        else if (aktualnyUzytkownik->getRola() == "admin") {
            if (wybor == 1) wyswietlProdukty();
            else if (wybor == 2) dodajProdukt();
            else if (wybor == 3) usunProdukt();
            else if (wybor == 4) zamowDostawe();
            else if (wybor == 5) aktualnyUzytkownik = nullptr;
            else std::cout << "Niepoprawna opcja menu.\n";
        }
    }
}