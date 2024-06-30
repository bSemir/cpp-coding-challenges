#include <iostream>
#include <stdexcept>

class StedniRacun {
private:
    int broj_racuna;
    double stanje_racuna;
    static int posljednji_br_racuna;
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
};

int StedniRacun::posljednji_br_racuna = 1000;

int main() {
    try {
//        StedniRacun r1(10.5);
        StedniRacun r2(10.55);
        std::cout << "Broj racuna: " << r2.DajBrojRacuna() << std::endl; // 1001
//        StedniRacun r3(9.99);
    } catch (const char *msg) {
        std::cout << "Greska: " << msg << std::endl;
    }
    return 0;
}