#include <iostream>
#include <cmath>

// class Tacka
class Tacka {
private:
    double x, y;
public:
    Tacka(double x, double y) : x(x), y(y) {}
    double DajX() const { return x; }
    double DajY() const { return y; }
    Tacka &Postavi(double x_, double y_) {
        if(x_ < 0 || y_ < 0) throw std::domain_error("Neispravne koordinate");
        this->x = x_;
        this->y = y_;
        return *this;
    }
    void Ispisi() const {
        std::cout << "(" << DajX() << "," << DajY() << ")" << std::endl;
    }
};

// class Krug
class Krug {
private:
    Tacka centar;
    double poluprecnik;
public:
    Krug(Tacka centar, double poluprecnik) : centar(centar), poluprecnik(poluprecnik) {
        if(poluprecnik <= 0) throw std::domain_error("Neispravan(negativan ili nula) poluprecnik");
    }
    Krug(double x, double y, double r) : centar(x, y), poluprecnik(r) {
        if(r <= 0) throw std::domain_error("Neispravan(negativan ili nula) poluprecnik");
    }
    Krug(Tacka centar, Tacka tacka_na_rubu) : centar(centar) {
        // poluprecnik kruga je jednak rastojanju izmedju centra i tacke na rubu
        poluprecnik = sqrt(pow(tacka_na_rubu.DajX() - centar.DajX(), 2) + pow(tacka_na_rubu.DajY() - centar.DajY(), 2));
    }
    Krug &Postavi(Tacka centar_, double poluprecnik_) {
        if(poluprecnik <= 0) throw std::domain_error("Neispravan(negativan ili nula) poluprecnik");
        this->centar = centar_;
        this->poluprecnik = poluprecnik_;
        return *this;
    }
    Krug &Postavi(double x, double y, double r) {
        if(r <= 0) throw std::domain_error("Neispravan(negativan ili nula) poluprecnik");
        centar.Postavi(x, y);
        poluprecnik = r;
        return *this;
    }
    Krug &Postavi(Tacka centar_, Tacka tacka_na_rubu) {
        this->centar = centar_;
        poluprecnik = sqrt(pow(tacka_na_rubu.DajX() - centar.DajX(), 2) + pow(tacka_na_rubu.DajY() - centar.DajY(), 2));
        return *this;
    }
    Tacka DajCentar() const { return centar; }
    double DajPoluprecnik() const { return poluprecnik; }
    double DajObim() const { return 2 * poluprecnik * 3.14; }
    double DajPovrsinu() const { return poluprecnik * poluprecnik * 3.14; }
    void Ispisi() const {
        std::cout << "{ ( " << DajCentar().DajX() << ", " << DajCentar().DajY() << " ), " << DajPoluprecnik() << " }" << std::endl;
    }
};

int main() {
    // testiranje klase Tacka
    std::cout << "----- Tacka -----\n";
    Tacka t(1, 2);
    t.Ispisi();
    t.Postavi(3, 4).Ispisi();
    std::cout << t.DajX() << " " << t.DajY() << std::endl;

    // testiranje klase Krug
    std::cout << "\n----- Krug -----\n";
    // konstruktor s dva parametra (Tacka i double)
    Krug k1 = Krug(Tacka(1, 2), 3);
    std::cout << "K1 -> "; k1.Ispisi();
    // konstruktor s tri parametra (double, double, double)
    Krug k2 = Krug(1, 2, 3);
    std::cout << "K2 -> "; k2.Ispisi();
    // konstruktor s dva parametra (Tacka i Tacka)
    Krug k3 = Krug(Tacka(1, 2), Tacka(4, 6));
    std::cout << "K3 -> "; k3.Ispisi();

    return 0;
}

