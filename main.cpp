#include <iostream>
#include <map>
#include <vector>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include "tabela.hpp"
#include <iterator>
#include <sstream>
#include <array>
#include <cstring>
#include <algorithm>


int main() {

    auto exit = bool(false);


    auto BazaDanych = std::vector<Tabela>();

    /*
baza to vector zlozony z tabel
baza jest 1 w programie i jest tworzona od razu po starcie programu

tabela (nowa klasa) sklada sie z
nazwy - string
kolumn - vector ze stringow
wiersz - mapa par zlozonych z id i map ktore maja kolumna-wartosc


Przykladowe polecenia:
DODAJ TABELE tab IMIE NAZWISKO
DODAJ WIERSZ tab JAN NOWAK
POKAZ WIERSZE tab GDZIE IMIE = JAN
POKAZ WIERSZEPOSORTOWANE tab WEDLUG_KOLUMNY IMIE (ODWROTNIE)
POKAZ WIERSZE tab GDZIE IMIE = JAN ORAZ NAZWISKO = NOWAK
POKAZ WIERSZE tab GDZIE IMIE = JAN LUB NAZWISKO = NOWAK
ZMIEN WARTOSC tab PRZY_KOLUMNIE IMIE NA ola GDZIE IMI = jan
USUN TABELE tab
USUN WIERSZ tab 3

     */

    fmt::println("Witam w programie do pracy nad baza danych.\n"
                 "Aby zaczac napisz polecenie i wcisnij klawisz ENTER\n"
                 "Jesli nie wiesz od czego zaczac, mozesz uzyc polecenia POMOC");


    //przykładowe dla skrocenia pisania nowych tabel przy kazdym uruchomieniu programu

    auto testVector = std::vector<std::string>{"DODAJ","TABELE", "OSOBA", "IMIE", "NAZWISKO"};
    BazaDanych.emplace_back(NowaTabela(testVector));
    testVector = std::vector<std::string>{"DODAJ", "WIERSZ", "OSOBA", "JAN", "KOWALSKI"};
    NowyWiersz(BazaDanych[0],testVector);
    testVector = std::vector<std::string>{"DODAJ", "WIERSZ", "OSOBA", "MAREK", "NOWAK"};
    NowyWiersz(BazaDanych[0],testVector);
    testVector = std::vector<std::string>{"DODAJ", "WIERSZ", "OSOBA", "MICHAL", "CICHY"};
    NowyWiersz(BazaDanych[0],testVector);
    testVector = std::vector<std::string>{"DODAJ", "WIERSZ", "OSOBA", "JAN", "CICHY"};
    NowyWiersz(BazaDanych[0],testVector);
    testVector = std::vector<std::string>{"DODAJ", "WIERSZ", "OSOBA", "ADAM", "NOWAK"};
    NowyWiersz(BazaDanych[0],testVector);


    while (exit==false) {
        fmt::println("Podaj polecenie");
        //zrodlo dla podzialu string na vector: https://www.geeksforgeeks.org/cpp-string-to-vector-using-delimiter/
        auto polecenie = std::string();
        std::getline(std::cin, polecenie);
        auto vecPol = std::vector<std::string>();
        auto ss = std::stringstream(polecenie);
        auto tempStr = std::string();
        while (std::getline(ss, tempStr, ' ')) {
            vecPol.emplace_back(tempStr);
        }
        fmt::println("Wprowadzone polecenie:\n{}", polecenie);

        //tutaj dobry bylby switch ale na stringi niestety nie dziala

        if (vecPol[0] == "DODAJ")
        {
            if(vecPol[1]=="TABELE")
                BazaDanych.emplace_back(NowaTabela(vecPol));
            else if(vecPol[1]=="KOLUMNE")
            {
                auto czyZmiana = false;
                for (Tabela& dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZmiana = true;
                        fmt::println("Znaleziono tabele");
                        NowaKolumna(dk,vecPol);
                        fmt::println("{}",dk.kolumny);
                    }
                }
                if(!czyZmiana)
                    fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
            else if(vecPol[1]=="WIERSZ")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela& dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        NowyWiersz(dk,vecPol);
                    }
                }
                if(czyZnalezionoTabele) fmt::println("Znaleziono tabele");
                else fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
            else BlednaSkladnia(vecPol);
        }

        else if (vecPol[0] == "ZMIEN") {
            if (vecPol[1]=="WARTOSC")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela& dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        fmt::println("Znaleziono tabele");
                        ZmienWartosc(dk,vecPol);
                        fmt::println("test wyszedl jesli dziala {}",dk.wiersze[2]);
                    }
                }
                if(!czyZnalezionoTabele)
                    fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
            else fmt::println("Popraw skladnie");
        }
        else if (vecPol[0] == "USUN") {
            if (vecPol[1]=="WIERSZ")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela& dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        fmt::println("Znaleziono tabele");
                        UsunWiersz(dk,vecPol);
                        //fmt::println("test wyszedl jesli dziala {}",dk.wiersze[2]);
                    }
                }
                if(!czyZnalezionoTabele)
                fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
            else if (vecPol[1]=="TABELE")
            {
                fmt::println("Proba usuniecia tabeli {}",vecPol[2]);
                auto czyZnalezionoTabele = false;
                auto bdIterator = BazaDanych.begin();
                for(int i = 0;i<BazaDanych.size();i++,bdIterator++){
                    if(bdIterator->nazwa==vecPol[2])
                    {
                        //fmt::println("znaleziono tabele");
                        czyZnalezionoTabele=true;
                        BazaDanych.erase(bdIterator);
                        //fmt::println("usunieto tabele");
                    }
                }

                if(czyZnalezionoTabele) fmt::println("Znaleziono i usunieto tabele");
                else fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
            else fmt::println("Popraw skladnie");
        }
        else if (vecPol[0] == "POKAZ") {
            if (vecPol[1] == "KOLUMNY")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        PokazKolumny(dk);
                    }
                }
                if(czyZnalezionoTabele) fmt::println("Znaleziono tabele");
                else fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
           else if (vecPol[1] == "WIERSZE")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        if (vecPol[3]=="GDZIE")
                            PokazWiersze(dk,vecPol);
                        else PokazWiersze(dk);
                    }
                }
                if(czyZnalezionoTabele) fmt::println("Znaleziono tabele");
                else fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
           else if (vecPol[1] == "POSORTOWANEWIERSZE")
            {
                auto czyZnalezionoTabele = false;
                for (Tabela dk:BazaDanych) {
                    if (dk.nazwa==vecPol[2]) {
                        czyZnalezionoTabele = true;
                        PokazPosortowaneWiersze(dk,vecPol);
                    }
                }
                if(czyZnalezionoTabele) fmt::println("Znaleziono tabele");
                else fmt::println("Nie znaleziono tabeli o nazwie: {}",vecPol[2]);
            }
           else fmt::println("Bledna skladnia\n"
                             "Poprawna skladnia dla polecenia POKAZ wyglada nastepujaco:\n"
                             "\nPOKAZ WIERSZE nazwa_tabeli GDZIE nazwa_kolumny = wartosc\n"
                             "POKAZ POSORTOWANEWIERSZE nazwa_tabeli WEDLUG_KOLUMNY nazwa_kolumny (ODWROTNIE)\n"
                             "POKAZ WIERSZE nazwa_tabeli GDZIE nazwa_kolumny1 = wartosc1 ORAZ/LUB nazwa_kolumny2 = wartosc2\n");

        }
        else if (vecPol[0] == "WYCZYSC")
        {
            fmt::println("Czy na pewno chcesz wyczyscic baze danych z wszystkich tabel? (tak/nie)");
            auto test = std::string("nie wiem");
            while (test!="tak" and test!="nie")
            {
                std::getline(std::cin, test);
            }
            if(test=="tak") BazaDanych.clear();
        }

        else if (vecPol[0] == "KONIEC") {
            fmt::println("Program konczy dzialanie");
            exit = true;
        }
        else if (vecPol[0] == "POMOC") {
            fmt::println("W tym jezyku bazodanowym mozesz uzyc 6 polecen");
            fmt::println("\"DODAJ\", \"USUN\", \"ZMIEN\", \"WYCZYSC\", \"POMOC\" i \"KONIEC\"");
            fmt::println("Przykladowe polecenia:\n"
                         "DODAJ TABELE tab IMIE NAZWISKO\n"
                         "DODAJ WIERSZ tab JAN NOWAK\n"
                         "POKAZ WIERSZE tab GDZIE IMIE = JAN\n"
                         "POKAZ WIERSZEPOSORTOWANE tab WEDLUG_KOLUMNY IMIE (ODWROTNIE)\n"
                         "POKAZ WIERSZE tab GDZIE IMIE = JAN ORAZ NAZWISKO = NOWAK\n"
                         "POKAZ WIERSZE tab GDZIE IMIE = JAN LUB NAZWISKO = NOWAK\n"
                         "ZMIEN WARTOSC tab PRZY_KOLUMNIE IMIE NA ola GDZIE IMI = jan\n"
                         "USUN TABELE tab\n"
                         "USUN WIERSZ tab 3");
        }
        else       BlednaSkladnia();

    }


    return 0;
}
