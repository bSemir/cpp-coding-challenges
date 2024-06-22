#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

// abstract base class
class Spremnik {
protected:
    double tezina;
    std::string naziv_sadrzaja;

public:
    Spremnik(double tezina, std::string naziv_sadrzaja)
            : tezina(tezina), naziv_sadrzaja(naziv_sadrzaja) {}

    virtual ~Spremnik() {};

    double DajTezinu() const { return tezina; };

    virtual double DajUkupnuTezinu() const = 0;

    virtual void Ispisi() const = 0;

    virtual Spremnik *DajKopiju() const = 0;
};

// Class Sanduk - interface
class Sanduk : public Spremnik {
private:
    std::vector<double> tezine_predmeta;

public:
    Sanduk(double tezina, std::string naziv, std::vector<double> tezine)
            : Spremnik(tezina, naziv), tezine_predmeta(tezine) {}

    double DajUkupnuTezinu() const override;

    void Ispisi() const override;

    Spremnik *DajKopiju() const override;
};

// class Sanduk implementation
double Sanduk::DajUkupnuTezinu() const {
    double ukupna_tezina = DajTezinu();
    return std::accumulate(tezine_predmeta.begin(), tezine_predmeta.end(),
                           ukupna_tezina);
    //   for (int i = 0; i < tezine_predmeta.size(); i++)
    //     ukupna_tezina += tezine_predmeta[i];
    //   return ukupna_tezina;
}

void Sanduk::Ispisi() const {
    std::cout << "Vrsta spremnika: Sanduk\n";
    std::cout << "Sadrzaj: " << naziv_sadrzaja << std::endl;
    std::cout << "Tezine predmeta: ";
    for (double i: tezine_predmeta)
        std::cout << i << " ";
    std::cout << "(kg)" << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Ukupna tezina: " << this->DajUkupnuTezinu() << " (kg)"
              << std::endl;
}

Spremnik *Sanduk::DajKopiju() const { return new Sanduk(*this); }

// Class Vreca - innterface
class Vreca : public Spremnik {
private:
    double tezina_materije;

public:
    Vreca(double tezina, std::string naziv, double tezina_materije)
            : Spremnik(tezina, naziv), tezina_materije(tezina_materije) {}

    double DajUkupnuTezinu() const override;

    Spremnik *DajKopiju() const override;

    void Ispisi() const override;
};

// class Vreca implementation
double Vreca::DajUkupnuTezinu() const { return tezina_materije + DajTezinu(); }

void Vreca::Ispisi() const {
    std::cout << "Vrsta spremnika: Vreca\n";
    std::cout << "Sadrzaj: " << naziv_sadrzaja << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Tezina pohranjene materije: " << tezina_materije << " (kg)"
              << std::endl;
    std::cout << "Ukupna tezina: " << this->DajUkupnuTezinu() << " (kg)"
              << std::endl;
}

Spremnik *Vreca::DajKopiju() const { return new Vreca(*this); }

// Class Bure - interface
class Bure : public Spremnik {
private:
    double tezina_tecnosti; // gustina
    double zapremina_tecnosti;

public:
    Bure(double tezina, std::string naziv, double gustina_tecnosti_bureta,
         double zapremina_tecnosti_bureta)
            : Spremnik(tezina, naziv), tezina_tecnosti(gustina_tecnosti_bureta),
              zapremina_tecnosti(zapremina_tecnosti_bureta) {}

    double DajUkupnuTezinu() const override;

    Spremnik *DajKopiju() const override;

    void Ispisi() const override;
};

// class Bure implementation
void Bure::Ispisi() const {
    std::cout << "Vrsta spremnika: Bure\n";
    std::cout << "Sadrzaj: " << naziv_sadrzaja << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Specificna tezina tecnosti: " << tezina_tecnosti << " (kg/m^3)"
              << std::endl;
    std::cout << "Zapremina tecnosti: " << zapremina_tecnosti << " (l)"
              << std::endl;
    std::cout << "Ukupna tezina: " << this->DajUkupnuTezinu() << " (kg)"
              << std::endl;
}

double Bure::DajUkupnuTezinu() const {
    return tezina + (tezina_tecnosti * zapremina_tecnosti * 0.001);
}

Spremnik *Bure::DajKopiju() const { return new Bure(*this); }

// interface for class Skladiste
class Skladiste {
private:
    std::vector<std::shared_ptr<Spremnik>> spremnici;

public:
    Skladiste() {};

    Skladiste(const Skladiste &s);

    Skladiste(Skladiste &&s) noexcept;

    Skladiste &operator=(const Skladiste &s);

    Skladiste &operator=(Skladiste &&s) noexcept;

    ~Skladiste();

    Spremnik *DodajSanduk(double tezina, std::string naziv,
                          std::vector<double> tezine);

    Spremnik *DodajVrecu(double tezina, std::string naziv,
                         double tezina_materije);

    Spremnik *DodajBure(double tezina, std::string naziv,
                        double gustina_tecnosti_bureta,
                        double zapremina_tecnosti_bureta);

    Spremnik *DodajSpremnik(Spremnik *objekat, bool predati_vlasnistvo);

    void BrisiSpremnik(Spremnik *adress);

    const Spremnik &DajNajtezi() const = delete;

    const Spremnik &DajNajlaksi() const = delete;

    Spremnik &DajNajtezi();

    Spremnik &DajNajlaksi();

    int BrojPreteskih(int granica) const;

    void IzlistajSkladiste() const;

    void UcitajIzDatoteke(std::string ime_datoteke);
};

// Skladiste implementation

Skladiste::Skladiste(const Skladiste &s) {
    spremnici.reserve(s.spremnici.size());
    for (const auto &spremnik: s.spremnici) {
        auto kopija = spremnik->DajKopiju();
        spremnici.push_back(std::shared_ptr<Spremnik>(kopija));
    }
}

Skladiste::Skladiste(Skladiste &&s) noexcept: spremnici(s.spremnici) {
    s.spremnici.resize(0);
}

Skladiste &Skladiste::operator=(const Skladiste &s) {
    if (this == &s)
        return *this;
    std::vector<std::shared_ptr<Spremnik>> temp_novi;
    //   temp_novi.resize(s.spremnici.size());
    for (const auto &spremnik: s.spremnici) {
        // auto kopija = spremnik->DajKopiju();
        temp_novi.push_back(std::shared_ptr<Spremnik>(spremnik->DajKopiju()));
    }
    spremnici = std::move(temp_novi);
    return *this;
}

Skladiste &Skladiste::operator=(Skladiste &&s) noexcept {
    if (this == &s)
        return *this;
    std::swap(spremnici, s.spremnici);
    s.spremnici.resize(0);
    return *this;
}

Skladiste::~Skladiste() {
    for (int i = 0; i < spremnici.size(); i++)
        spremnici.at(i) = nullptr;
    spremnici.resize(0);
}

Spremnik *Skladiste::DodajSanduk(double tezina, std::string naziv,
                                 std::vector<double> tezine) {
    auto sanducic = std::make_shared<Sanduk>(tezina, naziv, tezine);
    spremnici.push_back(sanducic);
    return sanducic.get(); // sirovi pok
}

Spremnik *Skladiste::DodajVrecu(double tezina, std::string naziv,
                                double tezina_materije) {
    auto vrecica = std::make_shared<Vreca>(tezina, naziv, tezina_materije);
    spremnici.push_back(vrecica);
    return vrecica.get();
}

Spremnik *Skladiste::DodajBure(double tezina, std::string naziv,
                               double gustina_tecnosti_bureta,
                               double zapremina_tecnosti_bureta) {
    auto burence = std::make_shared<Bure>(tezina, naziv, gustina_tecnosti_bureta,
                                          zapremina_tecnosti_bureta);
    spremnici.push_back(burence);
    return burence.get();
}

Spremnik *Skladiste::DodajSpremnik(Spremnik *objekat, bool predati_vlasnistvo) {
    std::shared_ptr<Spremnik> p;
    if (predati_vlasnistvo)
        p = std::shared_ptr<Spremnik>(objekat);
    else
        p = std::shared_ptr<Spremnik>(objekat->DajKopiju());

    spremnici.push_back(p);
    return p.get();
}

void Skladiste::BrisiSpremnik(Spremnik *adress) {
    spremnici.erase(
            std::remove_if(spremnici.begin(), spremnici.end(),
                           [adress](const auto &p) { return p.get() == adress; }),
            spremnici.end());
}

Spremnik &Skladiste::DajNajlaksi() {
    if (spremnici.size() == 0)
        throw std::range_error("Skladiste je prazno");
    return **std::min_element(
            spremnici.begin(), spremnici.end(),
            [](std::shared_ptr<Spremnik> s1,
               std::shared_ptr<Spremnik> s2) { // const auto &s2?
                return s1->DajTezinu() < s2->DajTezinu();
            });
}

Spremnik &Skladiste::DajNajtezi() {
    if (spremnici.empty())
        throw std::range_error("Skladiste je prazno");
    return **std::max_element(
            spremnici.begin(), spremnici.end(),
            [](std::shared_ptr<Spremnik> s1, std::shared_ptr<Spremnik> s2) {
                return s1->DajTezinu() < s2->DajTezinu();
            });
}

int Skladiste::BrojPreteskih(int granica) const {
    return count_if(spremnici.begin(), spremnici.end(),
                    [granica](std::shared_ptr<Spremnik> s) {
                        return s->DajUkupnuTezinu() > granica;
                    });
};

void Skladiste::IzlistajSkladiste() const {
    Skladiste temp(*this);
    std::sort(temp.spremnici.begin(), temp.spremnici.end(),
              [](std::shared_ptr<Spremnik> a, std::shared_ptr<Spremnik> b) {
                  return a->DajUkupnuTezinu() > b->DajUkupnuTezinu();
              });

    for (const auto &spremnik: temp.spremnici)
        spremnik->Ispisi();
}

void Skladiste::UcitajIzDatoteke(std::string ime_datoteke) {
    std::ifstream ulazni_tok(ime_datoteke);
    if (!ulazni_tok)
        throw std::logic_error("Trazena datoteka ne postoji");

    spremnici.clear();

    char oznaka;
    std::string ime;

    while (true) {
        oznaka = ulazni_tok.get();
        if (oznaka == EOF)
            return;
        if (oznaka != 'S' && oznaka != 'V' && oznaka != 'B') {
            ulazni_tok.setstate(std::ios::failbit);
            break;
        }
        char space = ulazni_tok.get();
        if (space != ' ') {
            ulazni_tok.setstate(std::ios::failbit);
            break;
        }
        std::getline(ulazni_tok, ime);
        double tez;
        ulazni_tok >> tez;
        if (!ulazni_tok)
            break;
        if (oznaka == 'S') {
            int d;
            ulazni_tok >> d;
            if (!ulazni_tok)
                break;
            std::vector<double> duzine(d);
            for (int i = 0; i < d; i++)
                ulazni_tok >> duzine[i];
            DodajSanduk(tez, ime, duzine);
        } else if (oznaka == 'V') {
            double t_m;
            ulazni_tok >> t_m;
            DodajVrecu(tez, ime, t_m);
        } else if (oznaka == 'B') {
            double gus, zap;
            ulazni_tok >> gus >> zap;
            DodajBure(tez, ime, gus, zap);
        }

        // if (ulazni_tok.peek() == '\n' || ulazni_tok.peek() == EOF)
        //   ulazni_tok.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // if (ulazni_tok.peek() == EOF)
        //   break;
        if (!ulazni_tok)
            break;
        if (ulazni_tok.get() == EOF)
            return;
    }
    //   if (!ulazni_tok.eof()) {
    //     if (!ulazni_tok.bad())
    //       throw std::logic_error("Datoteka sadrzi besmislene podatke");
    //     else
    //       throw std::logic_error("Problemi pri citanju datoteke");
    //   }
    if (!ulazni_tok.bad())
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
    else
        throw std::logic_error("Problemi pri citanju datoteke");
}

int main() {
    Skladiste ETF;
    ETF.DodajSanduk(55, "Voce", {1, 3, 5, 6});
    ETF.DodajVrecu(0.1, "Brasno", 25.5);
    ETF.DodajBure(5, "Krv", 1300, 150);
    ETF.IzlistajSkladiste();
    Skladiste ETF1(ETF);

    Skladiste ETF2;
    ETF2 = ETF1;
    ETF2.IzlistajSkladiste();
    Spremnik &najtezi_spremnik = ETF2.DajNajtezi();
    std::cout << "Tezina najtezeg (ETF2): " << najtezi_spremnik.DajTezinu() << std::endl;
    Spremnik &najlaksi_spremnik = ETF2.DajNajlaksi();
    std::cout << "Tezina najlakseg (ETF2): " << najlaksi_spremnik.DajTezinu() << std::endl;
    std::cout << "Ukupno preteskih: " << ETF.BrojPreteskih(40) << std::endl;

    Skladiste ETF3(std::move(ETF2));
    std::cout << "\nNakon premjestanja ETF2 u ETF3 i brisanja najtezeg spremnika: " << std::endl;
    ETF3.BrisiSpremnik(&najtezi_spremnik);
    ETF3.IzlistajSkladiste();

    // testiranje rada s datotekom
    //   try {
    //     Skladiste ETF;
    //     ETF.UcitajIzDatoteke("ROBA.TXT");
    //     ETF.IzlistajSkladiste();
    //   } catch (std::logic_error err) {
    //     std::cout << "Izuzetak: " << err.what() << std::endl;
    //   }
    return 0;
}