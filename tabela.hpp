#pragma once

#include <string>
#include <vector>
#include <map>


struct Tabela {
    std::string nazwa;
    int licznik;
    int licznikK;
    std::vector<std::string> kolumny;
    //std::vector<std::map<std::string,std::string>> wiersze;

    std::map<int, std::map<std::string,std::string>> wiersze;
    //std::map<int, std::vector<std::pair<std::string,std::string>>> wiersze;
    //std::map<std::string,std::string>> wiersze;
};

auto NowaTabela(std::vector<std::string>& vecPol) -> Tabela;
auto NowaKolumna(Tabela& tab,std::vector<std::string>& vecPol) -> void;
auto NowyWiersz(Tabela& tab,std::vector<std::string>& vecPol) -> void;
auto BlednaSkladnia() -> void;
auto BlednaSkladnia(std::vector<std::string>& vecPol) -> void;
auto PokazKolumny(Tabela& tab) -> void;
auto PokazWiersze(Tabela& tab) -> void;
auto PokazWiersze(Tabela& tab, std::vector<std::string>& vecPol) -> void;
auto PokazPosortowaneWiersze(Tabela& tab, std::vector<std::string>& vecPol) -> void;
auto ZmienWartosc(Tabela& tab, std::vector<std::string>& vecPol) -> void;
auto UsunWiersz(Tabela& tab, std::vector<std::string>& vecPol) -> void;