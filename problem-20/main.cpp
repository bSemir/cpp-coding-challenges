#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>

class Tim {
private:
    char ime_tima[21];
    int broj_odigranih;
    int broj_pobjeda;
    int broj_nerijesenih;
    int broj_poraza;
    int broj_datih;
    int broj_primljenih;
    int broj_poena;
public:
    Tim(const char ime[]);
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *DajImeTima() const { return ime_tima; };
    int DajBrojPoena() const { return broj_poena; };
    int DajGolRazliku() const { return broj_datih - broj_primljenih; };
    void IspisiPodatke() const;
};

Tim::Tim(const char ime[]) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0), broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0) {
    if (strlen(ime) > 20) throw std::range_error("Predugacko ime tima");
    std::strcpy(ime_tima, ime);
}

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
    broj_odigranih++;
    this->broj_datih += broj_datih;
    this->broj_primljenih += broj_primljenih;
    if(broj_datih > broj_primljenih) {
        broj_pobjeda++;
        broj_poena += 3;
    } else if(broj_datih == broj_primljenih) {
        broj_nerijesenih++;
        broj_poena++;
    } else {
        broj_poraza++;
    }
}

void Tim::IspisiPodatke() const {
    std::cout <<
              std::left << std::setw(20) << ime_tima <<
              std::right << std::setw(4) << broj_odigranih <<
              std::setw(4) << broj_pobjeda <<
              std::setw(4) << broj_nerijesenih <<
              std::setw(4) << broj_poraza <<
              std::setw(4) << broj_datih <<
              std::setw(4) << broj_primljenih <<
              std::setw(4) << broj_poena <<
              std::endl;
}

class Liga {
private:
    int broj_timova;
    const int max_br_timova;
    Tim **timovi;
    void dealociraj();
public:
    explicit Liga(int velicina_lige) : broj_timova(0), max_br_timova(velicina_lige), timovi(new Tim *[velicina_lige]{}) {};
    explicit Liga(std::initializer_list<Tim> lista_timova);
    ~Liga() { dealociraj(); }
    Liga(const Liga &l);
    Liga(Liga &&l);
    Liga &operator =(const Liga &l);
    Liga &operator =(Liga &&l);
    void DodajNoviTim(const char ime_tima[]);
    void RegistrirajUtakmicu(const char tim1[], const char tim2[],
                             int rezultat_1, int rezultat_2);
    void IspisiTimove() const;
    void IspisiTabelu() const;
};

void Liga::dealociraj() {
    for(int i = 0; i < broj_timova; i++) delete timovi[i];
    delete[] timovi;
}

// NOTE: we have to initialize attributes inside constructor initializer list because we have const attribute

// sequence constructor
Liga::Liga(std::initializer_list<Tim> lista_timova) : broj_timova(lista_timova.size()), max_br_timova(lista_timova.size()), timovi(new Tim*[max_br_timova]{}) {
    try {
        int i = 0;
        for(const auto &t : lista_timova) {
            timovi[i] = new Tim(t); // copy constructor of Tim is called
            i++;
        }
    } catch(...) {
        dealociraj();
        throw;
    }
}

// copy constructor, deep copy
Liga::Liga(const Liga &l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(new Tim*[l.max_br_timova]{}) {
    try {
        for (int i = 0; i < broj_timova; i++)
            timovi[i] = new Tim(*l.timovi[i]); // copy constructor of Tim is called
    } catch (...) {
        dealociraj();
        throw;
    }
}

// move constructor
Liga::Liga(Liga &&l) : broj_timova(l.broj_timova), max_br_timova(l.max_br_timova), timovi(l.timovi) {
    // literally steal the resources from l
    l.broj_timova = 0;
    l.timovi = nullptr;
}

int main() {

    return 0;
}