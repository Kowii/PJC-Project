#include <fmt/core.h>
#include <fmt/ranges.h>
#include <algorithm>
#include "tabela.hpp"



auto NowaTabela(std::vector<std::string>& vecPol) -> Tabela {
    auto nowa = Tabela(vecPol[2],1,0);
    for(int j = 3; j < vecPol.size(); j++)
    {
        nowa.kolumny.emplace_back(vecPol[j]);
        nowa.licznikK++;
    }
    fmt::println("Kolumny tabeli {} to: {}",nowa.nazwa,nowa.kolumny);
    return nowa;
}
auto NowaKolumna(Tabela& tab,std::vector<std::string>& vecPol) -> void
{
    for (int k = 3; k<vecPol.size(); k++)
    {
        tab.kolumny.emplace_back(vecPol[k]);
        tab.licznikK++;
    }
    fmt::println("aktualne kolumnty tabeli {} to: {}",tab.nazwa,tab.kolumny);
}
auto NowyWiersz(Tabela& tab,std::vector<std::string>& vecPol) -> void
{
    if((tab.licznikK+3)==vecPol.size())
    {
        auto temp = std::map<std::string, std::string>();

        for (int i = 3; i < vecPol.size(); i++) {
            temp[tab.kolumny[i - 3]] = vecPol[i];
        }

        tab.wiersze[tab.licznik] = temp;
        tab.licznik++;
    }
    else fmt::println("Bledne polecenie - liczba wartosci przekracza liczbe kolumn");
}
auto BlednaSkladnia()-> void {
    fmt::println("Bledna skladnia.\n"
                 "Uzyj polecenia POMOC aby dowiedziec sie wiecej.\n"
                 "Pamietaj o tym, ze wielkosc liter ma znaczenie");
}
auto BlednaSkladnia(std::vector<std::string>& vecPol) -> void{
    if (vecPol[0]=="DODAJ")
    {
        fmt::println("Polecenie DODAJ piszemy w nastepujacy sposob:\n"
                     "1) Przy dodawaniu tabeli: "
                     "\"DODAJ TABELE nazwa_tabeli [nazwy kolumn do dodania oddzielone spacjami]\" \n"
                     "2) Przy dodawaniu kolumny do tabeli: "
                     "\"DODAJ KOLUMNE nazwa_tabeli [nazwy kolumn do dodania oddzielone spacjami]\"\n"
                     "3) Przy dodawaniu wiersza do tabeli: "
                     "\"DODAJ WIERSZ nazwa_tabeli [wartosci do kolumn tabeli (wylaczajac ID)]\"");
    }
}

auto PokazKolumny(Tabela& tab) -> void
{
    fmt::println("Tabela {} ma nastepujace kolumny: {}",tab.nazwa,tab.kolumny);
}
auto PokazWiersze(Tabela& tab) -> void{

    fmt::println("Tabela {}: \n{}",tab.nazwa,tab.kolumny);
    for (std::pair e: tab.wiersze)
    {
        fmt::print("[\"{}\"",e.first);
        for(std::pair f:e.second)
        {
            fmt::print(", \"{}\"",f.second);
        }
        fmt::println("]");
    }
}
auto PokazPosortowaneWiersze(Tabela& tab, std::vector<std::string>& vecPol) -> void{

    fmt::println("Tabela {}: \n{}",tab.nazwa,tab.kolumny);
    auto sortVec = std::vector<std::pair<int,std::map<std::string,std::string>>>();
    auto tempTabMap = tab.wiersze;
    auto minW = std::pair<int,std::map<std::string,std::string>>();
    while (!tempTabMap.empty())
    {
        for(auto e: tempTabMap)
        {
            if (minW.first>0)
            {
                for(auto f:e.second)
                {
                    //fmt::println("Aktualny minW to {} \n Sprawdzane f to {}",minW,f);
                    if (f.first==vecPol[4] and (f.second.compare(minW.second[vecPol[4]]) < 0))
                    {
                        minW=e;
                        //fmt::println("zmiana minW na {}",e);
                    }
                }
                //fmt::println("koniec petli f");
            }
            else minW=e;
        }
       // fmt::println("koniec petli e");
        //fmt::println("aktualny stan temptabmap {}",tempTabMap);
        //fmt::println("minW = {}",minW);
        sortVec.emplace_back(minW);
        tempTabMap.erase(minW.first);
        minW.first=0;
        //fmt::println("stan sortvec to {}",sortVec);
        //fmt::println("stan temptabmap przed erase to {}",tempTabMap);
        //fmt::println("minW = {}",minW);
        //fmt::println("stan temptabmap po erase to {}",tempTabMap);
    }

    if(vecPol[5]=="ODWROTNIE") std::ranges::reverse(sortVec);
    for (std::pair e: sortVec)
    {
        fmt::print("[\"{}\"",e.first);
        for(std::pair f:e.second)
        {
            fmt::print(", \"{}\"",f.second);
        }
        fmt::println("]");
    }
}

auto PokazWiersze(Tabela& tab, std::vector<std::string>& vecPol) -> void
{
    if (vecPol[7]=="ORAZ")
    {

        fmt::println("Tabela {}: \n{}",tab.nazwa,tab.kolumny);
        for (std::pair e: tab.wiersze)
        {
            auto test1 = bool(false);
            auto test2 = bool(false);
            for (std::pair f: e.second)
            {
                if(f.first==vecPol[4] and f.second==vecPol[6])
                {
                    test1 = true;
                }
                else if(f.first==vecPol[8] and f.second==vecPol[10])
                {
                    test2 = true;
                }
            }
            if (test1 and test2) {
                fmt::print("[\"{}\"", e.first);
                for (std::pair f: e.second) {
                    fmt::print(", \"{}\"", f.second);
                }
                fmt::println("]");
            }
        }
    }
    else if (vecPol[7]=="LUB")
    {

        fmt::println("Tabela {}: \n{}",tab.nazwa,tab.kolumny);
        for (std::pair e: tab.wiersze)
        {
            //fmt::println("Sprawdzenie e czyli {}",e);
            auto test1 = bool(false);
            auto test2 = bool(false);
            for (std::pair f: e.second)
            {
                //fmt::println("f.first to {} a f.second to {}",f.first,f.second);
                //fmt::println("vecPol4 to {} a vecpol6 to {}",vecPol[4],vecPol[6]);
                if(f.first==vecPol[4] and f.second==vecPol[6])
                {
                    test1 = true;
                    //fmt::println("Znaleziono w wierszu {} zgadzajace sie {}",e,f);
                }
                else if(f.first==vecPol[8] and f.second==vecPol[10])
                {
                    test2 = true;
                    //fmt::println("Znaleziono w wierszu {} zgadzajace sie {}",e,f);
                }
                //else fmt::println("cos poszlo nie tak");
            }
            if (test1 or test2) {
                fmt::print("[\"{}\"", e.first);
                for (std::pair f: e.second) {
                    fmt::print(", \"{}\"", f.second);
                }
                fmt::println("]");
            }
        }
    }
    else if(vecPol[5]=="=")
    {

        fmt::println("Tabela {}: \n{}",tab.nazwa,tab.kolumny);
        for (std::pair e: tab.wiersze)
        {
            //fmt::println("Sprawdzenie e czyli {}",e);
            auto mamyto = bool(false);
            for (std::pair f: e.second)
            {
                //fmt::println("f.first to {} a f.second to {}",f.first,f.second);
                //fmt::println("vecPol4 to {} a vecpol6 to {}",vecPol[4],vecPol[6]);
                if(f.first==vecPol[4] and f.second==vecPol[6])
                {
                    mamyto = true;
                    //fmt::println("Znaleziono w wierszu {} zgadzajace sie {}",e,f);
                }
                //else fmt::println("cos poszlo nie tak");
            }
            if (mamyto) {
                fmt::print("[\"{}\"", e.first);
                for (std::pair f: e.second) {
                    fmt::print(", \"{}\"", f.second);
                }
                fmt::println("]");
            }
        }
    }
    else fmt::println("brak = , na vecpol6 jest {}",vecPol[6]);
}


auto ZmienWartosc(Tabela& tab, std::vector<std::string>& vecPol) -> void

{
    if(vecPol[3]=="PRZY_KOLUMNIE")
    {
        auto mamyto = bool(false);
        for (std::pair e: tab.wiersze)
        {

            for (std::pair f: e.second)
            {
                if(f.first==vecPol[8] and f.second==vecPol[10])
                {
                    mamyto = true;
                    tab.wiersze[e.first][vecPol[4]]=vecPol[6];
                }
            }
        }
        if(mamyto) fmt::println("Udalo sie dokonac zmiany");
        else fmt::println("Nie znaleziono pasujacych wartosci");
    }
    else fmt::println("brak = , na vecpol6 jest {}",vecPol[6]);
    //fmt::println("test wyszedl jesli dziala {}",tab.wiersze[2]);
}

auto UsunWiersz(Tabela& tab, std::vector<std::string>& vecPol) -> void
{
    auto iter = tab.wiersze.begin();
        auto test=false;
    for (int i = 0; i < tab.wiersze.size(); i++,iter++) {
        if ((*iter).first==stoi(vecPol[3]))//zrodlo : https://www.geeksforgeeks.org/convert-string-to-int-in-cpp/
        {
            //fmt::println("sukces");
            tab.wiersze.erase(iter);
            test=true;
        }
        //else fmt::println("nie znaleziono tym razem");
    }
    if (test) fmt::println("Pomyslnie usunieto z tabeli {} wiersz o ID {}",tab.nazwa,vecPol[3]);
    else fmt::println("Nie znaleziono w tabeli {} wiersza o ID {}",tab.nazwa,vecPol[3]);
}