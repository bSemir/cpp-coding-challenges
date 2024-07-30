#include <iostream>
#include <iterator>
#include <stdexcept>
#include <list>


template<typename tip>
void aritmeticka_sredina(tip pocetak, tip iza_kraja) {
    int vel = std::distance(pocetak, iza_kraja);
//     std::cout << "size: " << vel << std::endl;
    if (vel < 2) throw std::domain_error("Prekratak slijed");
}

int main() {
    try {
        std::list<int> l{3, 8, 6, 2, 4, 1, 5};
        aritmeticka_sredina(l.begin(), l.end());
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}