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

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
