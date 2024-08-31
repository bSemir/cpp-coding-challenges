#include <iostream>
#include <set>

template<typename IterTip, typename FunTip>
auto Mapiraj(const IterTip &kontejner, FunTip f) {
    using T = std::remove_reference_t<IterTip>;
    T C; // or IterTip C
    for (auto &e: kontejner)
        C.insert(f(e));
    return C;
}

int suma_cifara(int n) {
    int suma = 0;
    while (n != 0) {
        suma += std::abs(n % 10);
        n /= 10;
    }
    return suma;
}

int main() {
    std::cout << "Unesite broj elemenata skupa: ";
    int n;
    std::cin >> n;
    std::set<int> s;
    std::cout << "Unesite elemente: ";
    for (int i = 0; i < n; i++) {
        int broj;
        std::cin >> broj;
        s.insert(broj);
    }
    std::cout << "Novi skup: ";
    auto ns = Mapiraj(s, [](int x) {
        return suma_cifara(x);
    });
    for (auto &el: ns) std::cout << el << " ";
    return 0;
}
