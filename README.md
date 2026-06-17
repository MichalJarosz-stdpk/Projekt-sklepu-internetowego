System Zarządzania Sklepem (C++)
Aplikacja konsolowa symulująca działanie sklepu internetowego z podziałem na role użytkowników (Klient oraz Administrator).

🛠️ Architektura i Główne Funkcje
Program opiera się na trzech głównych modułach:

1. Klasa Sklep (Serce aplikacji)
uruchom() – zarządzanie sesją i menu.

zaloguj() – logowanie użytkownika.

wyswietlProdukty() – wyświetla produkty(nazwa,cena,ilość w magazynie).

wczytajProdukty() / zapiszProdukty() – odczytuje i zapisuje produkty.

2. Klasa Produkt
zdejmijZStanu(int ile) – zmiejsza ilość produktów po zakupie.

dodajIlosc(int ile) – Zwiększa stan produktu w magazynie.

3. Hierarchia Klas Uzytkownik 
Klasa bazowa Uzytkownik oraz klasy pochodne Klient i Admin.

wyswietlMenu() – wyswietla menu przypisane do roli konta .

Zarządzanie Pamięcią i Destruktory
W projekcie zastosowano dynamiczną alokację pamięci  do przechowywania obiektów użytkowników w kontenerze std::vector<Uzytkownik*>.

Rola Destruktorów w Projekcie:
Wirtualny Destruktor virtual ~Uzytkownik():
Oznaczenie destruktora klasy bazowej jako virtual gwarantuje, że podczas usuwania obiektu przez wskaźnik typu bazowego (Uzytkownik*),
 program poprawnie wywoła destruktor klasy pochodnej (~Admin() lub ~Klient()), czyszcząc całą składową pamięć.

Destruktor Sklep::~Sklep():
Automatycznie uruchamia się w momencie zamykania aplikacji.
Wykonuje 2 czynności
Trwały zapis danych: Wywołuje funkcję zapiszProdukty(), utrwalając aktualny stan magazynu w pliku .txt.

Czyszczenie pamięci RAM: bezpiecznie zwalnia pamięć zarezerwowaną dla użytkowników:
