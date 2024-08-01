#include <iostream>
#include <iterator>
#include <stdexcept>
#include <list>


template<typename tip>
auto aritmeticka_sredina(tip pocetak, tip iza_kraja) {
    // duzina
    int size = std::distance(pocetak, iza_kraja);
    if (size < 2) throw std::domain_error("Prekratak slijed");
    // sredina
    tip iter_sredina = std::next(pocetak, size / 2);
    auto suma1 = *pocetak, suma2 = *iter_sredina;
    // sum of first half
    while (++pocetak != iter_sredina) suma1 += *pocetak;
    // sum of second half
    while (++iter_sredina != iza_kraja) suma2 += *iter_sredina;
    // prosjeci
    auto p1 = suma1 / double(size / 2), p2 = suma2 / double(size + 1 / 2);
    if (p1 > p2) return p1;
    return p2;
}

int main() {
    try {
        std::list<int> l{3, 8, 6, 2, 4, 1, 5};
        auto x = aritmeticka_sredina(l.begin(), l.end());
        std::cout << "Result: " << x << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}

// NOTE:
// “advance” modificira proslijeđeni iterator da pokazuje na novo mjesto, a
// “next” ne, nego samo vraća novi iterator koji pokazuje na novo mjesto kao rezultat