#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>


template<typename tip>
auto KreirajDinamickuKopiju2D(tip &c) {
    using TipElemenata = std::remove_reference_t<decltype(c[0][0])>;
//    TipElemenata **niz;

    // number of rows
    int br_redova = 0;
    for (auto p = begin(c); p != end(c); p++) br_redova++;

    // declaration
    TipElemenata **niz{};
    try {
        // allocation
        niz = new TipElemenata *[br_redova];
        for (int i = 0; i < br_redova; i++) {
            int br_elemenata_reda = 0;
            for (auto p = begin(c[i]); p != end(c[i]); p++) br_elemenata_reda++;
            niz[i] = new TipElemenata[br_elemenata_reda];
            // copy elements from c to niz
            for (int j = 0; j < br_elemenata_reda; j++) niz[i][j] = c[i][j];
        }
    } catch (...) {
        for (int i = 0; i < br_redova; i++) delete[] niz[i];
        delete[] niz;
        throw std::range_error("Nedovoljno memorije!");
    }
    return niz;
}

int main() {
    std::cout << "Unesite broj redova kvadratne matrice: ";
    int n;
    std::cin >> n;
    std::vector<std::deque<int>> matrica(n, std::deque<int>(n));
    std::cout << "Unesite elemente: ";
    for (auto &red: matrica) {
        for (auto &el: red) {
            std::cin >> el;
        }
    }
    int **dinamicka = KreirajDinamickuKopiju2D(matrica);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << dinamicka[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}