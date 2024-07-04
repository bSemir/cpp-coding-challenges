#include <iostream>
#include <stdexcept>
#include <fstream>

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
    SigurniRacun(int stanje, int pin) : StedniRacun(stanje), pin(pin), otvoren(false) {
        if (!jeLiCetvorocifren(pin))
            throw "Neispravan PIN";
//        this->pin = pin; // koristimo this jer je ime parametra isto kao i ime atributa
//        otvoren = false;
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

    StedniRacun &operator[](int broj_racuna) { return *racuni[nadjiRacun(broj_racuna)]; }

    const StedniRacun &operator[](int broj_racuna) const { return *racuni[nadjiRacun(broj_racuna)]; }

    friend std::ostream &operator<<(std::ostream &tok, const Banka &b);

    void SacuvajUDatoteku(std::string ime_datoteke);
};

int Banka::nadjiRacun(int broj_racuna) const {
    for (int i = 0; i < broj_racuna; i++)
        if (racuni[i]->DajBrojRacuna() == broj_racuna) return i;

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
    // TODO: radi kad se otkomentarise linija ispod
//    if (treutno_otvoreni != nullptr) throw "Racun je vec otvoren (OtvoriRacun)";
    if (DaLiJeSiguran(racuni[indeks])) {
        SigurniRacun *sr = static_cast<SigurniRacun *>(racuni[indeks]);
        if (pin_ == PIN_upravitelja)
            pin_ = sr->pin; // ako je upravitelj, onda moze otvoriti racun bez pina
        sr->OtvoriRacun(pin_);
    }
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
    for (int i = 0; i < broj_racuna; i++) {
        OtvoriRacun(racuni[i]->DajBrojRacuna(), pin);
        *treutno_otvoreni *= kamatna_stopa;
        ZatvoriRacun();
    }
    treutno_otvoreni = pomocni;

}

void Banka::ZatvoriRacun() {
    if (treutno_otvoreni != nullptr && DaLiJeSiguran(treutno_otvoreni))
        static_cast<SigurniRacun *>(treutno_otvoreni)->ZatvoriRacun(PIN_upravitelja);
    treutno_otvoreni = nullptr;
}

// std::ostream &operator<<(std::ostream &tok, const Banka &b) {
//    auto pomocni = b.treutno_otvoreni;
//    for(int i = 0; i < b.broj_racuna; i++) {
//        OtvoriRacun(b.racuni[i]->DajBrojRacuna(), b.PIN_upravitelja);
//        tok << *b.treutno_otvoreni << std::endl;
//        ZatvoriRacun();
//    }
//    b.treutno_otvoreni = pomocni;
//    return tok;
//}

void Banka::SacuvajUDatoteku(std::string ime_datoteke) {
    std::ofstream izlaz(ime_datoteke);
    if (!izlaz)
        throw std::logic_error("Datoteka se ne moze otvoriti");
    izlaz << "PIN upravitelja: " << PIN_upravitelja << std::endl;
    SigurniRacun *pomocni = dynamic_cast<SigurniRacun *>(treutno_otvoreni);
    for (int i = 0; i < broj_racuna; i++) {
        OtvoriRacun(racuni[i]->DajBrojRacuna(), PIN_upravitelja);
        izlaz << *(*treutno_otvoreni);
        if (DaLiJeSiguran(racuni[i]))
            izlaz << "," << static_cast<SigurniRacun *>(racuni[i])->pin;
        izlaz << std::endl;
        ZatvoriRacun();
    }
    treutno_otvoreni = pomocni;
    if (!izlaz) throw std::logic_error("Greska prilikom upisa u datoteku");
    izlaz.close();
}

int main() {
    try {
        Banka b(1234);

        b.KreirajRacun(300, 1234);
        b.OtvoriRacun(1001, 1234);
        b += 50;
        b.KreirajRacun(200, 1234);
        b.OtvoriRacun(1002, 1234);
        b += 100;
        b.KreirajRacun(400, 1234);
        b.OtvoriRacun(1003, 1234);
        b += 200;

        b.SacuvajUDatoteku("racuni.txt");
    } catch (const char *msg) {
        std::cout << "Izuzetak: " << msg << std::endl;
    }
    return 0;
}