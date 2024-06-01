#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>
#include <algorithm>

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

void Tim::ObradiUtakmicu(int dati, int primljeni) {
    if(dati < 0 || primljeni < 0) throw std::range_error("Neispravan broj golova");
    broj_odigranih++;
    broj_datih += dati;
    broj_primljenih += primljeni;
    if(dati > primljeni) {
        broj_pobjeda++;
        broj_poena += 3;
    } else if(dati == primljeni) {
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
    int gdjeJeTim(const char tim[]) const;
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

// NOTE: must initialize attributes inside constructor initializer list because we have const attribute

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
    l.broj_timova = 0; // important because of delete timovi[i] (illegal pointer dereference in `dealociraj` method)
    l.timovi = nullptr;
}

// assignment operator
Liga &Liga::operator=(const Liga &l) {
    if(l.max_br_timova != max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(this != &l) {
        Tim **new_teams = new Tim*[l.max_br_timova] {};
        try {
            for(int i = 0; i < broj_timova; i++) new_teams[i] = new Tim(*l.timovi[i]);
        } catch (...) {
            for(int i = 0; i < broj_timova; i++) delete new_teams[i];
            delete [] new_teams;
            throw;
        }
        dealociraj();
        timovi = new_teams;
        broj_timova = l.broj_timova;
    }
    return *this;
}

// move assignment operator
Liga &Liga::operator=(Liga &&l) {
    if(max_br_timova != l.max_br_timova) throw std::logic_error("Nesaglasni kapaciteti liga");
    if(&l != this) {
        dealociraj();
        timovi = l.timovi;
        broj_timova = l.broj_timova;
        l.broj_timova = 0;
        l.timovi = nullptr;
    }
    return *this;
}

void Liga::DodajNoviTim(const char *ime_tima) {
    if(broj_timova >= max_br_timova) throw std::logic_error("Dostignut maksimalni broj timova");
    timovi[broj_timova++] = new Tim(ime_tima);
}

int Liga::gdjeJeTim(const char *tim) const {
    for(int i = 0; i < broj_timova; i++)
        if(std::strcmp(timovi[i]->DajImeTima(), tim) == 0) return i;
    return -1;
//    auto it = std::find_if(timovi, timovi + broj_timova, [tim](Tim *t) { return std::strcmp(t->DajImeTima(), tim) == 0; });
//    return it == timovi + broj_timova ? -1 : it - timovi;
}

void Liga::RegistrirajUtakmicu(const char *tim1, const char *tim2, int rezultat_1, int rezultat_2) {
    int i = gdjeJeTim(tim1), j = gdjeJeTim(tim2);
    if(i == -1 || j == -1) throw std::logic_error("Tim nije nadjen");
    if(rezultat_1 < 0 || rezultat_2 < 0) throw std::range_error("Neispravan broj golova");
    timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
    timovi[j]->ObradiUtakmicu(rezultat_2, rezultat_1);
}

void Liga::IspisiTimove() const {
    for(int i = 0; i < broj_timova; i++) timovi[i]->DajImeTima();
}

void Liga::IspisiTabelu() const {
//     old version that can modify the array (sort it) even though it is const. We don't want that
//    std::sort(timovi, timovi + broj_timova, [](Tim *t1, Tim *t2) {
//        if(t1->DajBrojPoena() != t2->DajBrojPoena()) return t1->DajBrojPoena() > t2->DajBrojPoena();
//        if(t1->DajGolRazliku() != t2->DajGolRazliku()) return t1->DajGolRazliku() > t2->DajGolRazliku();
//        return std::strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0;
//    });
    Tim **kopija_timova = new Tim*[broj_timova];
    std::copy(timovi, timovi + broj_timova, kopija_timova);
    std::sort(kopija_timova, kopija_timova + broj_timova, [](Tim *t1, Tim *t2) {
        if(t1->DajBrojPoena() != t2->DajBrojPoena()) return t1->DajBrojPoena() > t2->DajBrojPoena();
        if(t1->DajGolRazliku() != t2->DajGolRazliku()) return t1->DajGolRazliku() > t2->DajGolRazliku();
        return std::strcmp(t1->DajImeTima(), t2->DajImeTima()) < 0;
    });
    for(int i = 0; i < broj_timova; i++) kopija_timova[i]->IspisiPodatke();
    delete [] kopija_timova; // delete the copy
}

int main() {

    return 0;
}