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
    bool jeLiCetvorocifren(int broj) {
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

    friend std::ostream &operator<<(std::ostream &tok, const SigurniRacun &r) {
        if (r.otvoren)
            return tok << "PIN: " << r.pin << " Broj racuna: " << r.DajBrojRacuna() << ", Stanje: " << *r;
    }
};

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