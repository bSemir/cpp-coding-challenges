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

// TODO: Implement inherited class SigurniRacun

int main() {
    try {
//        StedniRacun r1(10.5);
        StedniRacun r2(10.55);
        std::cout << "Broj racuna: " << r2.DajBrojRacuna() << std::endl; // 1001
        std::cout << "Stanje racuna: " << *r2 << std::endl; // 10.55
        r2 += 5.5;
        std::cout << "Stanje racuna nakon dodavanja: " << *r2 << std::endl; // 16.05
        r2 -= 10.5;
        std::cout << "Stanje racuna nakon oduzimanja: " << *r2 << std::endl; // 5.55
        r2 *= 10;
        std::cout << "Stanje racuna nakon kamate: " << *r2 << std::endl; // 6.105
//        StedniRacun r3 = r2 + 5.5;
//        std::cout << "Stanje racuna nakon dodavanja: " << *r3 << std::endl; // 11.605
//        StedniRacun r3(9.99);
        std::cout << "Operator '<<': " << r2 << std::endl; // Broj racuna: 1001, Stanje: 6.105
    } catch (const char *msg) {
        std::cout << "Izuzetak: " << msg << std::endl;
    }
    return 0;
}