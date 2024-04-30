#include <iostream>
#include <map>

template <typename tipElemenata>
struct Cvor {
    tipElemenata element;
    Cvor<tipElemenata> *veza;
};

template <typename tipElemenata>
Cvor<tipElemenata> *KreirajPovezanuListu(tipElemenata zavrsni) {
    Cvor<tipElemenata> *pocetak = nullptr, *prethodni = nullptr;
    for(;;) {
        tipElemenata element;
        std::cin >> element;
        if(element == zavrsni) return pocetak; // ako je unesen zavrsni element, vracamo pokazivac na pocetak liste
        Cvor<tipElemenata> *novi = new Cvor<tipElemenata>{element, nullptr}; // kreiranje novog cvora
        if(!pocetak) pocetak = novi; // ako je lista prazna, novi cvor postaje pocetak liste
        else prethodni->veza = novi; // ako lista nije prazna, veza prethodnog cvora pokazuje na novi cvor
        prethodni = novi; // prethodni cvor postaje novi cvor (trenutni)
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
