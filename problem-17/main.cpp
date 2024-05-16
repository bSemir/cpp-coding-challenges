// TP 2023/2024: Zadaća 3, Zadatak 2
#include <cctype>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>>
        IndeksPojmova;

typedef std::map<std::string, std::vector<std::string>> Knjiga;

std::string PretvoriUVelikaSlova(const std::string &str) {
    std::string result;
    for (char c : str)
        result += std::toupper(c);
    return result;
}

bool IspravnaRijec(const std::string &rijec) {
    for (char c : rijec) {
        if (!std::isalnum(c))
            return false;
    }
    return true;
}

std::map<std::string, std::set<std::tuple<std::string, int, int>>> KreirajIndeksPojmova(const Knjiga &k) {
    std::map<std::string, std::set<std::tuple<std::string, int, int>>> indeks_pojmova;

    for (const auto &poglavlje : k) {
        const std::string &naziv_poglavlja = poglavlje.first;
        const std::vector<std::string> &stranice = poglavlje.second;

        for (int i = 0; i < stranice.size(); ++i) {
            const std::string &sadrzaj_stranice = stranice[i];

            for (int j = 0; j < sadrzaj_stranice.length(); ++j) {
                if (std::isalnum(sadrzaj_stranice[i]) &&
                    (j == 0 || !std::isalnum(sadrzaj_stranice[j - 1]))) {
                    std::string rijec;
                    int pocetak = j;
                    while (j < sadrzaj_stranice.length() && std::isalnum(sadrzaj_stranice[j])) {
                        rijec += std::toupper(sadrzaj_stranice[j]);
                        j++;
                    }
                    indeks_pojmova[rijec].insert(std::make_tuple(naziv_poglavlja, i + 1, pocetak + 1));
                }
            }
        }
    }
    return indeks_pojmova;
}

void IspisiIndeksPojmova(
        const std::map<std::string, std::set<std::tuple<std::string, int, int>>>
        &indeks) {
    std::cout << "\nKreirani indeks pojmova:" << std::endl;
    for (const auto &par : indeks) {
        std::cout << par.first << ": ";
        bool first = true;
        for (const auto &pozicija : par.second) {
            if (!first) { std::cout << ", "; }
            first = false;
            std::cout << std::get<0>(pozicija) << "/" << std::get<1>(pozicija) << "/"
                      << std::get<2>(pozicija);
        }
        std::cout << std::endl;
    }
}

std::set<std::tuple<std::string, int, int>>
PretraziIndeksPojmova(const std::string &rijec, const IndeksPojmova &indeks) {
    if (!IspravnaRijec(rijec))
        throw std::domain_error("Neispravna rijec");
    auto it = indeks.find(PretvoriUVelikaSlova(rijec));
    if (it == indeks.end())
        return {};
    return it->second; // vraca set pozicija, npr {("XIV", 5, 6), ("XV", 3, 4)}
}

int main() {
    std::string naziv_poglavlja;
    int broj_stranice = 1;
    Knjiga k;

    while (true) {
        std::cout << "Unesite naziv poglavlja: ";
        std::getline(std::cin, naziv_poglavlja);
        if (naziv_poglavlja.empty())
            break;
        std::vector<std::string> stranice;
        while (true) {
            std::cout << "\nUnesite sadrzaj stranice " << broj_stranice << ":\n";
            std::string sadrzaj_stranice;
            std::getline(std::cin, sadrzaj_stranice);
            if (sadrzaj_stranice.empty())
                break;
            stranice.push_back(sadrzaj_stranice);
            broj_stranice++;
        }
        k[naziv_poglavlja] = stranice;
        broj_stranice = 1; // resetovanje broja stranice za novo poglavlje
    }

    auto indeks = KreirajIndeksPojmova(k);
    IspisiIndeksPojmova(indeks);

    for (;;) {
        std::string rijec;
        std::cout << "\nUnesite rijec: ";
        std::getline(std::cin, rijec);

        if (!IspravnaRijec(rijec)) {
            std::cout << "Neispravna rijec!";
            continue;
        }

        if (rijec.empty()) {
            std::cout << "Dovidjenja!";
            break;
        }

        try {
            auto pozicije = PretraziIndeksPojmova(rijec, indeks);
            if (pozicije.empty()) {
                std::cout << "Rijec nije nadjena!";
            } else {
                std::cout << "\nRijec nadjena na pozicijama: ";
                for (const auto &pozicija : pozicije) {
                    std::cout << std::get<0>(pozicija) << "/" << std::get<1>(pozicija)
                              << "/" << std::get<2>(pozicija);
                    if (pozicija != *pozicije.rbegin()) {
                        std::cout << " ";
                    }
                }
            }
        } catch (std::domain_error &e) {
            std::cout << "IZUZETAK: " << e.what();
        }
    }
    return 0;
}