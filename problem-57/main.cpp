#include <iostream>
#include <list>


template<typename tip>
std::list<tip> SortirajListu(std::list<tip> &l) {
    std::list<tip> lista;
    auto x = l.begin();
    auto it = lista.begin();
    // sort
    while (x != l.end()) {
        it = lista.begin();
        while (it != lista.end() && *it < *x) {
            it++;
        }
        lista.insert(it, *x);
        x++;
    }
    return lista;
}

int main() {
    std::cout << "Koliko ima elemenata: ";
    int n;
    std::cin >> n;
    std::list<int> l(n);
    std::cout << "Unesite elemente: ";
    auto it = l.begin();
    for (int i = 0; i < n; i++) {
        std::cin >> *it;
        it++;
    }
    std::list<int> rez = SortirajListu(l);
    std::cout << "Sortirana lista: ";
    for (auto x: rez) {
        std::cout << x << " ";
    }
    return 0;
}
