#include <iostream>
#include <stdexcept>

class StedniRacun {
private:
    int broj_racuna;
    double stanje_racuna;
    static int posljednji_br_racuna;

    virtual std::ostream &pomocna_za_ispis(std::ostream &tok) const {
        return tok << "Broj racuna: " << broj_racuna << ", Stanje: " << stanje_racuna;
    }

protected:
    static bool imaDvijeDecimale(double iznos) {
        return (iznos * 100) == (int) (iznos * 100);
    }

public:
    // brojevi racuna se generisu automatski, od 1001 nadalje
    explicit StedniRacun(double stanje = 0) {
        if (stanje < 0 || !imaDvijeDecimale(stanje)) {
            throw "Neispravno stanje racuna";
        }
        if (stanje < 10)
            throw "Minimalno stanje racuna mora biti >= 10 KM";
        broj_racuna = ++posljednji_br_racuna;
        stanje_racuna = stanje;
    }

    StedniRacun(const StedniRacun &r) {
        broj_racuna = ++posljednji_br_racuna;
        stanje_racuna = r.stanje_racuna;
    }

    virtual ~StedniRacun() {}

    int DajBrojRacuna() const {
        return broj_racuna;
    }

    StedniRacun &operator=(const StedniRacun &r) {
        if (this == &r)
            return *this;
        stanje_racuna = r.stanje_racuna;
        // ne kopiramo broj racuna!
        return *this;
    }

    virtual double operator*() const {
        return stanje_racuna;
    }

    virtual StedniRacun &operator+=(double iznos) {
        if (iznos < 0 || !imaDvijeDecimale(iznos)) {
            throw "Neispravan iznos";
        }
        stanje_racuna += iznos;
        return *this;
    }

    virtual StedniRacun &operator-=(double iznos) {
        if (iznos < 0 || !imaDvijeDecimale(iznos)) {
            throw "Neispravan iznos";
        }
        if (iznos > stanje_racuna || stanje_racuna - iznos < 0)
            throw std::logic_error("Nemate dovoljno sredstava na racunu");
        stanje_racuna -= iznos;
        return *this;
    }

    virtual StedniRacun &operator*=(double kamata) {
        if (kamata < 0) {
            throw "Neispravna kamatna stopa";
        }
        stanje_racuna += stanje_racuna * kamata / 100;
        return *this;
    }

    StedniRacun operator+(double iznos) { return StedniRacun(*this) += iznos; } // svodi se na operator +=

    StedniRacun operator-(double iznos) { return StedniRacun(*this) -= iznos; }

    StedniRacun operator*(double iznos) { return StedniRacun(*this) *= iznos; }

    friend std::ostream &operator<<(std::ostream &tok, const StedniRacun &r) {
        // poziva se virtuelna funkcija pomocna_za_ispis izvedene klase jer je operator << prijateljska funkcija
        return r.pomocna_za_ispis(tok);
    }
};

int StedniRacun::posljednji_br_racuna = 1000;


class SigurniRacun : public StedniRacun {
private:
    int pin;
    mutable bool otvoren; // mutable jer se mijenja u const funkcijama

    friend class Banka; // Banka ce moci pristupiti privatnim atributima klase SigurniRacun
protected:
    static bool jeLiCetvorocifren(int broj) { // static jer ne zavisi od objekta
        return broj >= 1000 && broj <= 9999;
    }

public:
    SigurniRacun(double stanje, int pin) : StedniRacun(stanje) {
        if (!jeLiCetvorocifren(pin))
            throw "Neispravan PIN";
        this->pin = pin; // koristimo this jer je ime parametra isto kao i ime atributa
        otvoren = false;
    }

    void OtvoriRacun(int pin_) const {
        if (this->pin != pin_)
            throw "Neispravan PIN prilikom otvaranja racuna";
        otvoren = true;
    }

    void ZatvoriRacun(int pin) const {
        if (this->pin != pin)
            throw "Neispravan PIN prilikom zatvaranja racuna";
        otvoren = false;
    }

    StedniRacun &operator+=(double iznos) override {
        if (!otvoren)
            throw "Racun nije otvoren";
        return StedniRacun::operator+=(iznos); // pozivamo operator += iz bazne klase zato sto je on virtualan
    }

    StedniRacun &operator-=(double iznos) override {
        if (!otvoren)
            throw "Racun nije otvoren";
        return StedniRacun::operator-=(iznos);
    }

    StedniRacun &operator*=(double kamata) override {
        if (!otvoren)
            throw "Racun nije otvoren";
        return StedniRacun::operator*=(kamata);
    }

    double operator*() const override {
        if (!otvoren)
            throw "Racun nije otvoren";
        return StedniRacun::operator*();
    }

    std::ostream &pomocna_za_ispis(std::ostream &tok) const override {
        if (!otvoren)
            throw "Racun nije otvoren";
        return tok << "PIN: " << pin << " Broj racuna: " << DajBrojRacuna() << ", Stanje: " << StedniRacun::operator*()
                   << std::endl;

    }
};

class Banka {
private:
    int kapacitet;
    int broj_racuna;
    int PIN_upravitelja;
    StedniRacun *treutno_otvoreni;
    StedniRacun **racuni;

    int nadjiRacun(int broj_racuna) const;

    void realociraj();

    void dealociraj();

    StedniRacun &DajTrenutnoOtvoreni() const {
        if (treutno_otvoreni == nullptr)
            throw "Nijedan racun nije otvoren";
        return *treutno_otvoreni;
    }

public:
    Banka(int pin_upravitelja) : kapacitet(100), broj_racuna(0), PIN_upravitelja(pin_upravitelja),
                                 treutno_otvoreni(nullptr),
                                 racuni(new StedniRacun *[100]{}) {
        if (!SigurniRacun::jeLiCetvorocifren(pin_upravitelja))
            throw "Neispravan PIN upravitelja";
    }

    Banka(const Banka &b) : kapacitet(b.kapacitet), broj_racuna(b.broj_racuna), PIN_upravitelja(b.PIN_upravitelja),
                            treutno_otvoreni(b.treutno_otvoreni),
                            racuni(new StedniRacun *[kapacitet]{}) {
        try {
            for (int i = 0; i < broj_racuna; i++) {
                if (DaLiJeSiguran(b.racuni[i]))
                    racuni[i] = new SigurniRacun(
                            *static_cast<SigurniRacun *>(b.racuni[i])); // vrsimo downcast zato sto je b.racuni[i] tipa StedniRacun
                else
                    racuni[i] = new StedniRacun(*b.racuni[i]);
            }
        } catch (...) {
            dealociraj();
            throw;
        }
    }

    Banka(Banka &&b) noexcept: kapacitet(b.kapacitet), broj_racuna(b.broj_racuna), PIN_upravitelja(b.PIN_upravitelja),
                               treutno_otvoreni(b.treutno_otvoreni),
                               racuni(b.racuni) {
        b.broj_racuna = 0;
        b.racuni = nullptr;
    }

    Banka &operator=(const Banka &b) = delete;

    ~Banka() { dealociraj(); }

    void KreirajRacun(double stanje) {
        if (broj_racuna == kapacitet)
            throw "Dostignut maksimalan broj racuna";
        racuni[broj_racuna++] = new StedniRacun(stanje);
    }

    void KreirajRacun(double stanje, int pin) {
        if (broj_racuna == kapacitet)
            throw "Dostignut maksimalan broj racuna";
        racuni[broj_racuna++] = new SigurniRacun(stanje, pin);
    }

    static bool DaLiJeSiguran(StedniRacun *r) {
        return dynamic_cast<const SigurniRacun *>(r);
    }

    void ObrisiRacun(int broj_racuna);

    void OtvoriRacun(int broj_racuna);

    void OtvoriRacun(int broj_racuna, int pin_);

    void ZatvoriRacun();

    StedniRacun &operator+=(double iznos) {
        return DajTrenutnoOtvoreni() += iznos;
//         return *this += iznos;
    }

    StedniRacun &operator-=(double iznos) {
        return DajTrenutnoOtvoreni() -= iznos;
    }

    void ObracunajKamate(int pin, double kamatna_stopa);
};

int Banka::nadjiRacun(int broj_racuna) const {
    for (int i = 0; i < broj_racuna; i++) {
        if (racuni[i]->DajBrojRacuna() == broj_racuna)
            return i;
    }
    throw "Racun nije nadjen";
    // alternative way:
    StedniRacun **p = std::find_if(racuni, racuni + broj_racuna, [broj_racuna](StedniRacun *r) {
        return r->DajBrojRacuna() == broj_racuna;
    });
    if (p == racuni + broj_racuna)
        throw "Racun nije nadjen";
    return p - racuni;
}

void Banka::ObrisiRacun(int broj_racuna) {
    int indeks = nadjiRacun(broj_racuna);
    delete racuni[indeks];
//        for (int i = indeks; i < broj_racuna - 1; i++) racuni[i] = racuni[i + 1];
    racuni[indeks] = racuni[broj_racuna];
    racuni[broj_racuna--] = nullptr;
}

void Banka::OtvoriRacun(int broj_racuna) {
    int indeks = nadjiRacun(broj_racuna);
    if (treutno_otvoreni != nullptr)
        throw "Racun je vec otvoren (OtvoriRacun)";
    if (DaLiJeSiguran(racuni[indeks]))
        throw "Zasticen racun, potreban PIN za otvaranje (OtvoriRacun)";
//    racuni[indeks]->OtvoriRacun(PIN_upravitelja);
    treutno_otvoreni = racuni[indeks];
}

void Banka::OtvoriRacun(int broj_racuna, int pin_) {
    int indeks = nadjiRacun(broj_racuna);
    if (treutno_otvoreni != nullptr)
        throw "Racun je vec otvoren (OtvoriRacun)";
    if (!DaLiJeSiguran(racuni[indeks]))
        throw "Racun nije zasticen, ne treba PIN za otvaranje (OtvoriRacun)";
    auto *sr = static_cast<SigurniRacun *>(racuni[indeks]);
//    if(pin_ == PIN_upravitelja)
//        pin_ = sr->pin; // ako je upravitelj, onda moze otvoriti racun bez pina
    sr->OtvoriRacun(pin_);
    treutno_otvoreni = racuni[indeks];
}

void Banka::dealociraj() {
    for (int i = 0; i < broj_racuna; i++) delete racuni[i];
    delete[] racuni;

}

void Banka::realociraj() {
    if (broj_racuna == kapacitet) {
        kapacitet *= 2;
        auto **novi_prostor = new StedniRacun *[kapacitet]{};
        for (int i = 0; i < broj_racuna; i++) novi_prostor[i] = racuni[i];
        // or std::copu(racuni, racuni + broj_racuna, novi_prostor);
        delete[] racuni;
        racuni = novi_prostor;
    }
}

void Banka::ObracunajKamate(int pin, double kamatna_stopa) {
    if (pin != PIN_upravitelja)
        throw "Neispravan PIN upravitelja";
    if (kamatna_stopa < 0)
        throw "Neispravna kamatna stopa";
    // petlja moze poremetiti status koji je racun eventualno bio otvoren prije poziva OtvoriRacun
    // pa cemo ga sacuvati i vratiti na staro
    auto pomocni = treutno_otvoreni;
    for(int i = 0; i < broj_racuna; i++) {
        OtvoriRacun(racuni[i]->DajBrojRacuna(), pin);
        *treutno_otvoreni *= kamatna_stopa;
        ZatvoriRacun();
    }
    treutno_otvoreni = pomocni;

}

void Banka::ZatvoriRacun() {
    if(treutno_otvoreni != nullptr && DaLiJeSiguran(treutno_otvoreni))
        static_cast<SigurniRacun *>(treutno_otvoreni)->ZatvoriRacun(PIN_upravitelja);
    treutno_otvoreni = nullptr;
}

int main() {
    try {
        StedniRacun r1(100);
        StedniRacun r2(200);
        r1 += 50;
        r2 -= 100;
        r1 *= 2;
        std::cout << r1 << std::endl;
        std::cout << r2 << std::endl;
        SigurniRacun r3(300, 1234);
        r3.OtvoriRacun(1234);
        r3 += 100;
        r3 *= 2;
        std::cout << r3 << std::endl; // PIN: 1234 Broj racuna: 1003, Stanje: 800
        r3.ZatvoriRacun(1234);
    } catch (const char *msg) {
        std::cout << "Izuzetak: " << msg << std::endl;
    }
    return 0;
}