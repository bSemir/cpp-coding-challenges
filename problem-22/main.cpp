#include <iostream>

class Razlomak {
private:
    int brojnik, nazivnik;
public:
    // Konstruktor s dva parametra
    Razlomak (int brojnik = 0, int nazivnik = 1) {
        if(nazivnik == 0) throw std::domain_error("Nekorektan razlomak");
        Razlomak::brojnik = brojnik;
        Razlomak::nazivnik = nazivnik;
    }
    // operator unosa >> i ispisa <<
    friend std::istream &operator>>(std::istream &tok, Razlomak &r) {
        char znak;
        tok >> r.brojnik >> znak >> r.nazivnik;
        if(r.nazivnik == 0) throw std::domain_error("Nekorektan razlomak");
        return tok;
    }

    // metoda koja pojednostavljuje razlomak
    void pojednostavni() {
        int nzd = gcd(brojnik, nazivnik);
        brojnik /= nzd;
        nazivnik /= nzd;
    }

    // operator ispisa <<
    friend std::ostream &operator<<(std::ostream &tok, const Razlomak &r) {
        return tok << r.brojnik << "/" << r.nazivnik;
    }

    // operator + koji prima dva razlomka i vraca novi razlomak
    friend Razlomak operator+(const Razlomak &r1, const Razlomak &r2) {
        auto temp = Razlomak(r1.brojnik * r2.nazivnik + r2.brojnik * r1.nazivnik, r1.nazivnik * r2.nazivnik);
        temp.pojednostavni();
        return temp;
    }

    // operator - koji prima dva razlomka i vraca novi razlomak
    friend Razlomak operator-(const Razlomak &r1, const Razlomak &r2) {
        auto temp = Razlomak(r1.brojnik * r2.nazivnik - r2.brojnik * r1.nazivnik, r1.nazivnik * r2.nazivnik);
        temp.pojednostavni();
        return temp;
    }

    // prefiksni operator ++ koji povecava razlomak za 1
    Razlomak &operator ++() {
        brojnik += nazivnik;
        return *this;
    }

    // postfiksni operator ++ koji povecava razlomak za 1
    Razlomak operator ++(int) {
        Razlomak stari = *this;
        brojnik += nazivnik;
        return stari;
    }

    // prefiksni operator -- koji smanjuje razlomak za 1
    Razlomak &operator --() {
        brojnik -= nazivnik;
        return *this;
    }

    // postfiksni operator -- koji smanjuje razlomak za 1
    Razlomak operator --(int) {
        Razlomak stari_ = *this;
        brojnik -= nazivnik;
        return stari_;
    }

    // vraca najveci zajednicki djelioc (greates common divisor) dva broja
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a % b);
    }
};

int main() {
    Razlomak f1, f2;
    std::cout << "Unesite prvi razlomak u formatu brojnik/nazivnik: ";
    std::cin >> f1;
    std::cout << "Unesite drugi razlomak u formatu brojnik/nazivnik: ";
    std::cin >> f2;
    std::cout << "f1: " << f1 << std::endl;
    std::cout << "f2: " << f2 << std::endl;
    std::cout << "f1 + f2: " << f1+f2 << std::endl;
    std::cout << "f1 - f2: " << f1-f2 << std::endl;

    std::cout << "++f1: " << ++f1 << std::endl;
    std::cout<< "f1++: " << f1++ <<std::endl;

    std::cout << "--f1: " << --f1 << std::endl;
    std::cout << "f1--: " << f1-- << std::endl;
    std::cout<<"f1: "<<f1<<std::endl;

    return 0;
}