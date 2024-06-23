#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <climits>


struct Mjerenje {
    int dan;
    int mjesec;
    int godina;
    std::string komentar;
    int min_t, max_t;
    double prosjek;
};

int main() {
    std::string filename = "TEMPERATURE.TXT";
    std::ifstream ulazni_tok(filename);
    if (!ulazni_tok) {
        std::cout << "Datoteka TEMPERATURE.TXT ne postoji!" << std::endl;
        return 1;
    }
    Mjerenje m;
    std::vector<Mjerenje> mjerenja;
    char znak;
    while (ulazni_tok >> m.dan >> znak >> m.mjesec >> znak >> m.godina) {
        ulazni_tok.ignore(10000, '\n');
        std::getline(ulazni_tok, m.komentar);
        m.min_t = INT_MAX; // inicijalizacija na najvecu mogucu vrijednost za int
        m.max_t = INT_MIN;
        m.prosjek = 0;
        int broj_mjerenja = 0;
        int temperatura;
        while (true) {
            ulazni_tok >> temperatura >> std::ws;
            m.prosjek += temperatura; // zbrajanje temperatura
            broj_mjerenja++;
            if (temperatura < m.min_t) m.min_t = temperatura;
            if (temperatura > m.max_t) m.max_t = temperatura;
            if (ulazni_tok.peek() != ',')
                break; // ako nakon procitane temperature nije zarez, prekidamo petlju (kraj mjerenja)
            ulazni_tok >> znak;
        }
        m.prosjek /= broj_mjerenja;
        mjerenja.push_back(m);
    }
    std::cout << "Ukupno mjerenja: " << mjerenja.size() << std::endl;
    std::cout << "Mjerenja: " << std::endl;
    for (const auto &item: mjerenja) {
        std::cout << item.dan << "." << item.mjesec << "." << item.godina << " : " << item.komentar << " (min: "
                  << item.min_t << ", max: " << item.max_t << ", prosjek: " << item.prosjek << ")" << std::endl;
    }
    // provjera da li je kraj datoteke
//    if (!ulazni_tok.eof()) {
//        std::cout << "Greska prilikom citanja datoteke TEMPERATURE.TXT" << std::endl;
//        return 1;
//    }

    std::sort(mjerenja.begin(), mjerenja.end(), [](const Mjerenje &a, const Mjerenje &b) {
        if (a.godina != b.godina) return a.godina < b.godina;
        if (a.mjesec != b.mjesec) return a.mjesec < b.mjesec;
        if (a.dan != b.dan) return a.dan < b.dan;
        return a.prosjek < b.prosjek;
    });

    std::ofstream izlazni_tok("IZVJESTAJ.TXT");
    if (!izlazni_tok) {
        std::cout << "Greska prilikom otvaranja datoteke IZVJESTAJ.TXT" << std::endl;
        return 1;
    }
    for (const auto &item: mjerenja) {
        izlazni_tok << item.komentar << std::endl << "-------------------------------------" << std::endl
                    << "Datum mjerenja: "
                    << item.dan
                    << "." << item.mjesec << "." << item.godina << std::endl << "Minimalna temperatura: " << item.min_t
                    << std::endl << "Maksimalna temperatura: " << item.max_t << std::endl << "Prosjecna temperatura: "
                    << item.prosjek << std::endl << std::endl;
    }
    return 0;
}

// TODO: there is one Mjerenje object missing in the output file. Fix the bug.