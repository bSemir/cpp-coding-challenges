#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

template<typename T>
class Mapa {
private:
    std::vector<std::pair<std::string, T>> elementi;
public:
    Mapa() = default;

    Mapa(std::initializer_list<std::pair<std::string, T>> lista) {
        for (const auto &x: lista)
            elementi.push_back(x);
        izbaciDuplikate();
    }

    bool daLiPostoji(const std::string &kljuc) const {
        for (const auto &x: elementi)
            if (x.first == kljuc)
                return true;
        return false;
//        return std::binary_search(elementi.begin(), elementi.end(), kljuc);
    }

    void izbaciDuplikate() {
        std::sort(elementi.begin(), elementi.end());
        elementi.erase(std::unique(elementi.begin(), elementi.end()), elementi.end());
    }

    int DajVelicinu() const { return elementi.size(); }

    void DodajPar(const std::string &kljuc, const T &vrijednost) {
        if (!daLiPostoji(kljuc))
            elementi.push_back(std::make_pair(kljuc, vrijednost));
        else {
            for (auto &x: elementi)
                if (x.first == kljuc)
                    x.second = vrijednost;
        }
        izbaciDuplikate(); // do I need this here
    }

    void IzbrisiElement(const std::string &kljuc) {
        auto it = std::lower_bound(elementi.begin(), elementi.end(), std::make_pair(kljuc,
                                                                                    T())); // koristimo make_pair kao treci argument jer je potrebno da se proslijedi objekat istog tipa kao i elementi u vektoru
        if (it != elementi.end() && it->first == kljuc)
            elementi.erase(it);
        if (it != elementi.begin() && (it - 1)->first == kljuc) // ako je kljuc na prethodnom mjestu
            elementi.erase(it - 1);
    }

    const T &NadjiElement(const std::string &k) const {
        for (const auto &x: elementi)
            if (x.first == k)
                return x.second;
        throw std::logic_error("Kljuc nije pronadjen");
    }

    void IspisiMapu() const {
        for (const auto &x: elementi)
            std::cout << x.first << "/" << x.second << std::endl;
    }
};


int main() {
    try {
        Mapa<int> m1{{"a", 1},
                     {"b", 2},
                     {"c", 3},
                     {"d", 4},
                     {"e", 5},
                     {"f", 6},
                     {"g", 7},
                     {"h", 8},
                     {"i", 9},
                     {"j", 10},
                     {"k", 11},
                     {"l", 12},
                     {"m", 13},
                     {"n", 14},
                     {"o", 15},
                     {"p", 16},
                     {"q", 17},
                     {"r", 18},
                     {"s", 19},
                     {"t", 20},
                     {"u", 21},
                     {"v", 22},
                     {"w", 23},
                     {"x", 24},
                     {"y", 25},
                     {"z", 26}};
        m1.IspisiMapu();
        std::cout << std::endl;
        m1.DodajPar("a", 100);
        m1.IspisiMapu();
        std::cout << std::endl;
        m1.IzbrisiElement("a");
        m1.IspisiMapu();
        std::cout << std::endl;
        std::cout << m1.NadjiElement("b") << std::endl;
        std::cout << m1.DajVelicinu() << std::endl;
    } catch (std::logic_error &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
        return 0;
    }
}