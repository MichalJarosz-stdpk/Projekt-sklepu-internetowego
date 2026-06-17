#ifndef UZYTKOWNICY_H
#define UZYTKOWNICY_H

#include <string>

class Uzytkownik {
protected:
    std::string login;
    std::string haslo;
    std::string rola;

public:
    Uzytkownik(std::string l, std::string h, std::string r);
    virtual ~Uzytkownik() = default;

    std::string getLogin() const { return login; }
    std::string getHaslo() const { return haslo; }
    std::string getRola() const { return rola; }
    
    virtual void wyswietlMenu() = 0;
};

class Klient : public Uzytkownik {
public:
    Klient(std::string l, std::string h);
    void wyswietlMenu() override;
};

class Admin : public Uzytkownik {
public:
    Admin(std::string l, std::string h);
    void wyswietlMenu() override;
};

#endif