#include <iostream>
#include <string>

class Spremnik {
private:
    double tezina;
    std::string vrsta;
    std::string sadrzaj;
public:
    virtual ~Spremnik() {};
    Spremnik(const std::string &vrsta, double tezina, const char sadrzaj[]) : vrsta(vrsta), tezina(tezina), sadrzaj(sadrzaj)  {}
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
    Sanduk(double tezina, const char sadrzaj[], int broj_predmeta, double tezina_predmeta) : Spremnik("Sanduk", tezina, sadrzaj), broj_predmeta(broj_predmeta), tezina_predmeta(tezina_predmeta) {}
    virtual double DajUkupnuTezinu() const override {
        return DajTezinu() + broj_predmeta * tezina_predmeta;
    }
    Spremnik *DajKopiju() const override { return new Sanduk(*this); } // moze bez virtual.. redundant
};

class Bure : public Spremnik {
private:
    double tezina_tecnosti;
public:
    Bure(double tezina, const char sadrzaj[], double tezina_tecnosti) : Spremnik("Bure", tezina, sadrzaj), tezina_tecnosti(tezina_tecnosti) {}
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
    explicit Skladiste(int kapacitet) : broj_spremnika(0), kapacitet(kapacitet), spremnici(new Spremnik *[kapacitet]{}) {}
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
    void IzlistajSkladiste(std::ostream &izlas = std::cout) const;
    void UcitajPodatke(const char ime[]);
//    void Dealociraj();
};
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
