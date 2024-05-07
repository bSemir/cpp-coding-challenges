#include <iostream>

class Artikal {
private:
    std::string ime;
    float cijena;
public:
    Artikal &PostaviNazivICijenu(const std::string &ime, float cijena);
    float DajCijenu() const { return cijena; }
//    std::string DajNaziv() const { return ime; }
    Artikal &DodajPopust(float popust);
    static float ProsjecnaCijena(const Artikal *artikli, int n);
    friend void prikaziInformacije(const Artikal a[], int n);
};


Artikal &Artikal::PostaviNazivICijenu(const std::string &ime, float cijena) {
    this->ime = ime;
    this->cijena = cijena;
    return *this;
}

float Artikal::ProsjecnaCijena(const Artikal *artikli, int n) {
    float suma = 0;
    for (int i = 0; i < n; i++) {
        suma += artikli[i].DajCijenu();
    }
    return suma / n;
}

void prikaziInformacije(const Artikal a[], int n) {
    for(int i = 0; i < n; i++) std::cout << "Naziv: " << a[i].ime << ", cijena: " << a[i].cijena << std::endl;
}

Artikal &Artikal::DodajPopust(float popust) {
    cijena -= cijena * popust / 100;
    return *this;
}

int main() {
    // kreirati niz artikala
    Artikal artikli[3];
    artikli[0].PostaviNazivICijenu("Laptop", 1500);
    artikli[1].PostaviNazivICijenu("Monitor", 300);
    artikli[2].PostaviNazivICijenu("Mis", 20);

    std::cout << "Informacije o artiklima: " << std::endl;
    prikaziInformacije(artikli, 3);

    artikli[0].DodajPopust(10);
    artikli[1].DodajPopust(10);
    artikli[2].DodajPopust(10);

    std::cout << "\n";
    float popust = 10;
    std::cout << "Informacije o artiklima nakon dodavanja popusta od " << popust << "%: " << std::endl;
    prikaziInformacije(artikli, 3);

    std::cout << std::endl;
    std::cout << "Prosjecna cijena svih artikala: " << Artikal::ProsjecnaCijena(artikli, 3) << std::endl;

    return 0;
}
