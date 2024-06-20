#include <iostream>
#include <string>
#include <fstream>

class Spremnik {
private:
    double tezina;
    std::string vrsta;
    std::string sadrzaj;
public:
    virtual ~Spremnik() {};

    Spremnik(const std::string &vrsta, double tezina, const char sadrzaj[]) : vrsta(vrsta), tezina(tezina),
                                                                              sadrzaj(sadrzaj) {}

    double DajTezinu() const { return tezina; }

    virtual double DajUkupnuTezinu() const = 0;

    virtual Spremnik *DajKopiju() const = 0;

    void Ispisi(std::ostream &izlaz = std::cout) const {
        izlaz << "Vrsta spremnika: " << vrsta << std::endl
              << "Sadrzaj: " << sadrzaj << std::endl
              << "Vlastita tezina: " << tezina << " kg" << std::endl
              << "Ukupna tezina: " << DajUkupnuTezinu() << " kg" << std::endl;
    }
};

class Sanduk : public Spremnik {
    int broj_predmeta;
    double tezina_predmeta;
public:
    Sanduk(double tezina, const char sadrzaj[], int broj_predmeta, double tezina_predmeta) : Spremnik("Sanduk", tezina,
                                                                                                      sadrzaj),
                                                                                             broj_predmeta(
                                                                                                     broj_predmeta),
                                                                                             tezina_predmeta(
                                                                                                     tezina_predmeta) {}

    virtual double DajUkupnuTezinu() const override {
        return DajTezinu() + broj_predmeta * tezina_predmeta;
    }

    Spremnik *DajKopiju() const override { return new Sanduk(*this); } // moze bez virtual.. redundant
};

class Bure : public Spremnik {
private:
    double tezina_tecnosti;
public:
    Bure(double tezina, const char sadrzaj[], double tezina_tecnosti) : Spremnik("Bure", tezina, sadrzaj),
                                                                        tezina_tecnosti(tezina_tecnosti) {}

    virtual double DajUkupnuTezinu() const override {
        return DajTezinu() + tezina_tecnosti;
    }

    virtual Spremnik *DajKopiju() const override { return new Bure(*this); }
};

class Skladiste {
private:
    int broj_spremnika;
    int kapacitet;
    Spremnik **spremnici;
public:
    explicit Skladiste(int kapacitet) : broj_spremnika(0), kapacitet(kapacitet),
                                        spremnici(new Spremnik *[kapacitet]{}) {}

    ~Skladiste();

    Skladiste(const Skladiste &s);

    Skladiste(Skladiste &&s);

    Skladiste &operator=(Skladiste s);

//    Skladiste &operator=(Skladiste &&s);
    void DodajSanduk(double tezina, const char sadrzaj[], int broj_predmeta, double tezina_predmeta);

    void DodajBure(double tezina, const char sadrzaj[], double tezina_tecnosti);

    Spremnik &DajNajlaksi();

    const Spremnik &DajNajlaksi() const;

    Spremnik &DajNajtezi();

    const Spremnik &DajNajtezi() const;

    int BrojPreteskih(double granica) const;

    void IzlistajSkladiste(std::ostream &izlaz = std::cout) const;

    void UcitajPodatke(const char ime[]);
//    void Dealociraj();
};

// destructor
Skladiste::~Skladiste() {
    for (int i = 0; i < broj_spremnika; i++)
        delete spremnici[i];
    delete[] spremnici;
}

// copy constructor
Skladiste::Skladiste(const Skladiste &s) : broj_spremnika(s.broj_spremnika), kapacitet(s.kapacitet),
                                           spremnici(new Spremnik *[kapacitet]{}) {
    try {
        for (int i = 0; i < s.broj_spremnika; i++)
            spremnici[i] = s.spremnici[i]->DajKopiju();
    } catch (...) {
        for (int i = 0; i < broj_spremnika; i++)
            delete spremnici[i];
        delete[] spremnici;
        throw;
    }
}

// copy constructor without DajKopiju()
//Skladiste::Skladiste(const Skladiste &s) : broj_spremnika(s.broj_spremnika), kapacitet(s.kapacitet),
//                                           spremnici(new Spremnik *[s.kapacitet]{}) {
//    try {
//        for (int i = 0; i < broj_spremnika; i++) {
//            if (typeid(s.spremnici[i]) == typeid(Sanduk))
//                spremnici[i] = new Sanduk(*static_cast<Sanduk *>(s.spremnici[i]));
//            else
//                spremnici[i] = new Bure(*static_cast<Bure *>(s.spremnici[i]));
//        }
//    } catch (...) {
//        for (int i = 0; i < broj_spremnika; i++)
//            delete spremnici[i];
//        delete[] spremnici;
//        throw;
//    }
//}

Skladiste::Skladiste(Skladiste &&s) : broj_spremnika(s.broj_spremnika), kapacitet(s.kapacitet),
                                      spremnici(new Spremnik *[s.kapacitet]{}) {
    s.spremnici = nullptr;
    s.broj_spremnika = 0;
}

Skladiste &Skladiste::operator=(Skladiste s) {
//    if(this != &s) {
    std::swap(broj_spremnika, s.broj_spremnika);
    std::swap(kapacitet, s.kapacitet);
    std::swap(spremnici, s.spremnici);
//    }
    return *this;
}

void Skladiste::DodajSanduk(double tezina, const char sadrzaj[], int broj_predmeta, double tezina_predmeta) {
    if (broj_spremnika == kapacitet)
        throw std::domain_error("Popunjeno skladiste");
    spremnici[broj_spremnika++] = new Sanduk(tezina, sadrzaj, broj_predmeta, tezina_predmeta);
}

void Skladiste::DodajBure(double tezina, const char *sadrzaj, double tezina_tecnosti) {
    if (broj_spremnika == kapacitet)
        throw std::domain_error("Popunjeno skladiste");
    spremnici[broj_spremnika++] = new Bure(tezina, sadrzaj, tezina_tecnosti);
}

Spremnik &Skladiste::DajNajlaksi() {
    if (broj_spremnika == 0) throw std::range_error("Skladiste je prazno");
    // notice double dereferencing!
    return **std::min_element(spremnici, spremnici + broj_spremnika, [](Spremnik *s1, Spremnik *s2) {
        return s1->DajTezinu() < s2->DajTezinu();
    });
}

const Spremnik &Skladiste::DajNajlaksi() const {
    if (broj_spremnika == 0) throw std::range_error("Skladiste je prazno");
    return **std::min_element(spremnici, spremnici + broj_spremnika, [](Spremnik *s1, Spremnik *s2) {
        return s1->DajTezinu() < s2->DajTezinu();
    });
}

Spremnik &Skladiste::DajNajtezi() {
    if (broj_spremnika == 0) throw std::range_error("Skladiste je prazno");
    return **std::max_element(spremnici, spremnici + broj_spremnika, [](Spremnik *s1, Spremnik *s2) {
        return s1->DajTezinu() < s2->DajTezinu();
    });
}

const Spremnik &Skladiste::DajNajtezi() const {
    if (broj_spremnika == 0) throw std::range_error("Skladiste je prazno");
    return **std::max_element(spremnici, spremnici + broj_spremnika, [](Spremnik *s1, Spremnik *s2) {
        return s1->DajTezinu() < s2->DajTezinu();
    });
}

int Skladiste::BrojPreteskih(double granica) const {
    return std::count_if(spremnici, spremnici + broj_spremnika, [granica](Spremnik *spr) {
        return spr->DajUkupnuTezinu() > granica;
    });
}

void Skladiste::IzlistajSkladiste(std::ostream &izlaz) const {
    Spremnik **novi_spremnik = new Spremnik *[broj_spremnika];
    std::copy(spremnici, spremnici + broj_spremnika, novi_spremnik);
    std::sort(novi_spremnik, novi_spremnik + broj_spremnika, [](Spremnik *s1, Spremnik *s2) {
        return s1->DajUkupnuTezinu() > s2->DajUkupnuTezinu();
    });
    for (int i = 0; i < broj_spremnika; i++)
        novi_spremnik[i]->Ispisi(izlaz);
    delete[] novi_spremnik;
}

void Skladiste::UcitajPodatke(const char ime[]) {
    // ### format datoteke ###
    /*
    S Tepsije
    1.2 50 0.35
    B Maslinovo ulje
    0.8 16.5
    */
    for (int i = 0; i < broj_spremnika; i++) delete spremnici[i];
    broj_spremnika = 0;
    std::ifstream ulaz(ime);
    if (!ulaz) throw std::logic_error("Trazena datoteka ne postoji");
    std::logic_error greska("Datoteka sadrzi besmislene podatke"); // we'll use it quite often

    std::string tekst;
    // read line by line
    while (std::getline(ulaz, tekst)) { // read line and store it in tekst
        if (tekst.length() < 3 || tekst[1] != ' ')
            throw greska; // check if line is valid (at least 3 characters and space at 2nd position)
        std::string sadrzaj = tekst.substr(2, tekst.length() - 2); // get content of the line
        if (tekst[0] == 'S') {
            double tezina;
            double tezina_predmeta;
            int broj_predmeta;
            ulaz >> tezina >> broj_predmeta >> tezina_predmeta; //k read values from the line and store them in variables
            if (ulaz.bad()) break;
            if (!ulaz) throw greska;
            DodajSanduk(tezina, sadrzaj.c_str(), 1, tezina_predmeta); // c_str() returns const char*
        } else if (tekst[0] == 'B') {
            double tezina;
            double tezina_tecnosti;
            ulaz >> tezina >> tezina_tecnosti;
            if (ulaz.bad()) break;
            if (!ulaz) throw greska;
            DodajBure(tezina, sadrzaj.c_str(), tezina_tecnosti);
        } else throw greska;
        ulaz >> std::ws; // skip whitespace
    }
    if (!ulaz.eof()) throw std::logic_error("Problemi pri citanju datoteke");
}


int main() {
    Skladiste s(100);
    try {
        s.UcitajPodatke("skladiste.txt");
        s.IzlistajSkladiste();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}