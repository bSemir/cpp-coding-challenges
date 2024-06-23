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
            if (ulazni_tok.peek() != ',') break; // ako nije zarez, prekidamo petlju (kraj mjerenja)
            ulazni_tok >> znak;
        }
        m.prosjek /= broj_mjerenja;
        mjerenja.push_back(m);
    }
    return 0;
}
