#include <iostream>
#include <list>
#include <algorithm>


template<typename tip>
void SortirajListu(std::list<tip> &l) {
    for (auto it1 = l.begin(); it1 != l.end(); it1++) {
        auto min = it1;
        for (auto it2 = it1; it2 != l.end(); it2++) {
            if (*it2 < *min)
                min = it2;
        }
        std::swap(*it1, *min);
    }
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
    SortirajListu(l);
    std::cout << "Sortirana lista: ";
    for (auto x: l) std::cout << x << " ";

    return 0;
}
