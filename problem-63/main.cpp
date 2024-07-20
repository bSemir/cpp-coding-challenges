#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename tip, int br_elemenata>
void f(tip (&niz)[br_elemenata], tip &prvi, tip &drugi) {
    if (br_elemenata < 2) throw std::domain_error("Niz mora imati barem 2 elementa!");
    auto najmanji = std::min_element(std::begin(niz), std::end(niz));
    prvi = *najmanji;
    auto sljedeci_najmanji = std::min_element(std::begin(niz), std::end(niz), [najmanji](tip a, tip b) {
        if (a == *najmanji) return false;
        if (b == *najmanji) return true; // Ako je b najmanji, onda je a sigurno veci od b
        return a < b; 
    });
    if (sljedeci_najmanji == std::end(niz)) throw std::domain_error("Niz mora imati barem 2 različita elementa!");
    drugi = *sljedeci_najmanji;
}

int main() {
    try {
        int niz[10];
        std::cout << "Unesite elemente: ";
        for (auto &el: niz) std::cin >> el;
        int prvi, drugi;
        f(niz, prvi, drugi);
        std::cout << "Najmanji element: " << prvi << std::endl;
        std::cout << "Najmanji nakon njega je: " << drugi << std::endl;
    } catch (const std::domain_error &e) {
        std::cout << "Exception occurred: " << e.what() << "\n";
    }
    return 0;
}