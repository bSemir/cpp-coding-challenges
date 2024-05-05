#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <iomanip>

const int brojPredmeta = 8;

struct Datum {
    int dan, mjesec, godina;
};

struct Ucenik {
    std::string ime, prezime;
    Datum datum_rodjenja;
    int ocjene[brojPredmeta];
    double prosjek;
    bool prolaz;
};

void UnesiUcenike(std::vector<Ucenik*> &p_ucenici) {
    void UnesiJednogUcenika(Ucenik *p_ucenik);
    for(int i = 0; i < p_ucenici.size(); i++) {
        std::cout << "Unesite podatke za " << i + 1 << ". ucenika:\n";
        p_ucenici[i] = new Ucenik; // kreiranje novog objekta tipa Ucenik i smjestanje adrese u vektor
        UnesiJednogUcenika(p_ucenici[i]);
    }
}

void UnesiJednogUcenika(Ucenik *p_ucenik) {
    void UnesiDatum(Datum &datum);
    void UnesiOcjene(int ocjene[], int broj_predmeta);
    std::cout << "  Ime: ";
    std::cin >> p_ucenik->ime;
    std::cout << "  Prezime: ";
    std::cin >> p_ucenik->prezime;
    std::cout << "  Datum rodjenja(D/M/G): ";
    UnesiDatum(p_ucenik->datum_rodjenja);
    UnesiOcjene(p_ucenik->ocjene, brojPredmeta);
}

void UnesiDatum(Datum &datum) {
    char znak;
    std::cin >> datum.dan >> znak >> datum.mjesec >> znak >> datum.godina;
}

void UnesiOcjene(int ocjene[], int broj_predmeta) {
    void UnesiOcjenu(int &ocjena); // prototip funkcije, definicija je navedena kasnije.
    for(int i = 0; i < broj_predmeta; i++) {
        std::cout << "  Ocjena iz predmeta " << i + 1 << ". predmeta: ";
        UnesiOcjenu(ocjene[i]);
    }
}

void UnesiOcjenu(int &ocjena) {
    std::cin >> ocjena;
//    if(ocjena < 1 || ocjena > 5) {
//        throw std::domain_error("Ocjena nije validna!");
//    }
}

void ObradiUcenike(std::vector<Ucenik*> &p_ucenici) {
    void ObradiJednogUcenika(Ucenik *p_ucenik);
    for(Ucenik *p_ucenik : p_ucenici)
        ObradiJednogUcenika(p_ucenik);
    std::sort(p_ucenici.begin(), p_ucenici.end(), [](const Ucenik *p_u1, const Ucenik *p_u2) {
        return p_u1->prosjek > p_u2->prosjek;
    });
}

void ObradiJednogUcenika(Ucenik *p_ucenik) {
    // funkcija koja izracunava prosjek ocjena i postavlja prolaznost
    double suma_ocjena = 0;
    p_ucenik->prosjek = 1, p_ucenik->prolaz = false;
    for(int ocjena : p_ucenik->ocjene) {
        if(ocjena == 1) return;
        suma_ocjena += ocjena;
    }
    p_ucenik->prosjek = suma_ocjena / brojPredmeta;
    // p_ucenik->prolaz = p_ucenik->prosjek >= 2.5;
    p_ucenik->prolaz = true;
}

void IspisiIzvjestaj(const std::vector<Ucenik*> &p_ucenici) {
    void IspisiJednogUcenika(const Ucenik *p_ucenik);
    std::cout << "\n";
    for(const Ucenik *p_ucenik : p_ucenici) IspisiJednogUcenika(p_ucenik);
}

void IspisiJednogUcenika(const Ucenik *p_ucenik) {
    void IspisiDatum(const Datum &datum);
    std::cout << "Učenik " << p_ucenik->ime << " " << p_ucenik->prezime
              << " rođen ";
    IspisiDatum(p_ucenik->datum_rodjenja);
    if(p_ucenik->prolaz)
        std::cout << " ima prosjek " << std::setprecision(3) << p_ucenik->prosjek;
    else
        std::cout << " mora ponavljati razred";
    std::cout << std::endl;
}

void IspisiDatum(const Datum &datum) {
    std::cout << datum.dan << "/" << datum.mjesec << "/" << datum.godina;
}

void OslobodiMemoriju(std::vector<Ucenik*> &p_ucenici) {
    for(Ucenik *p_ucenik : p_ucenici) delete p_ucenik; // oslobadjanje memorije za svakog ucenika
}

int main() {
    void UnesiUcenike(std::vector<Ucenik*> &p_ucenici);
    void ObradiUcenike(std::vector<Ucenik*> &p_ucenici);
    void IspisiIzvjestaj(const std::vector<Ucenik*> &p_ucenici);
    void OslobodiMemoriju(std::vector<Ucenik*> &p_ucenici);
    int broj_ucenika;
    std::cout << "Koliko ima ucenika: ";
    std::cin >> broj_ucenika;
    try {
        std::vector<Ucenik*> p_ucenici(broj_ucenika);
        try {
            UnesiUcenike(p_ucenici);
        }
        catch(...) {
            OslobodiMemoriju(p_ucenici);
            throw;
        }
        ObradiUcenike(p_ucenici);
        IspisiIzvjestaj(p_ucenici);
        OslobodiMemoriju(p_ucenici);
    }
    catch(std::exception &e) {
        std::cout << "Izuzetak: " << e.what();
    }
    return 0;
}
