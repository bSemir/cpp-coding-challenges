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

template <typename tipElemenata>
void Zamijeni(Cvor<tipElemenata> *pocetak, std::map<tipElemenata, tipElemenata> &m) {
    Cvor<tipElemenata> *prethodni = nullptr;
    auto trenutni = pocetak;;
    while(trenutni) {
        auto it = m.find(trenutni->element);
        if(it != m.end()) {
            // zamjena
            trenutni->element = it->second;
            prethodni = trenutni; // prethodni cvor postaje trenutni cvor
            trenutni = trenutni->veza; // p pokazuje na sljedeci cvor

        } else {
            // brisanje
            Cvor<tipElemenata> *pom = trenutni;
            trenutni = trenutni->veza;
            delete pom;
            if(prethodni) prethodni->veza = trenutni;
            else pocetak = trenutni;
        }
    }
}
int main() {
    std::map<int, int> m {{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};
//    std::map<std::string, std::string> moj_rijecnik {{"jabuka", "apple"}, {"da", "yes"}, {"ne", "no"}, {"kako", "how"}, {"zasto", "why"}, };
    std::cout << "Unesite elemente liste (0 za kraj): \n";
    auto lista = KreirajPovezanuListu(0);
    Zamijeni(lista, m);
    std::cout << "Lista nakon zamjene: \n";
    for (auto p = lista; p != nullptr; p = p->veza) {
        std::cout << p->element << " ";
    }
    return 0;
}