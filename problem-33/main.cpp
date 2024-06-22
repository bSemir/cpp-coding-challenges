#include <iostream>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <set>

template<typename T>
class Skup {
private:
    std::vector<T> elementi;

    void sortiraj() {
        if (elementi.size() > 1)
            std::sort(elementi.begin(), elementi.end());
    }

public:
    Skup() = default;

    Skup(std::initializer_list<T> lista) : elementi(lista) {
        std::set<T> pomocni(elementi.begin(), elementi.end());
        elementi.clear();
        elementi.insert(elementi.end(), pomocni.begin(), pomocni.end());
        sortiraj();
    }

    int Velicina() const {
        return elementi.size();
    }

    void Dodaj(T element) {
        // ovo radi kao Insert
        if (std::find(elementi.begin(), elementi.end(), element) == elementi.end()) {
            elementi.push_back(element);
            sortiraj();
        }
    }

    void Izbrisi(T element) {
        // ovo radi kao Remove
        auto it = std::find(elementi.begin(), elementi.end(), element);
        if (it != elementi.end()) {
            elementi.erase(it);
        }
    }

    bool ImaLiGa(T element) const {
        return std::find(elementi.begin(), elementi.end(), element) != elementi.end();
    }

    void Ispisi() const {
        for (auto &element: elementi)
            std::cout << element << " ";
    }
};

int main() {
    Skup<int> s1;
    std::cout << "velicina praznog s1: " << s1.Velicina() << std::endl;

    Skup<double> s2 = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 7.7};
    std::cout << "elementi s2: ";
    s2.Ispisi();
    std::cout << std::endl;

    s2.Dodaj(8.8);
    std::cout << "da li je dodan element 8.8 (1 ako jeste 0 ako nije): ";
    std::cout << s2.ImaLiGa(8.8) << std::endl;
    std::cout << "elementi s2 nakon dodavanja 8.8: ";
    s2.Ispisi();

    std::cout << std::endl;
    s2.Izbrisi(0);
    std::cout << "da li je izbrisan element 0.0 (1 ako jeste 0 ako nije): ";
    std::cout << s2.ImaLiGa(0) << std::endl;
    std::cout << "elementi s2 nakon brisanja 0: ";
    s2.Ispisi();
    return 0;
}
