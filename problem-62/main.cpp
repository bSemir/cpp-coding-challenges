#include <iostream>
#include <set>


template<typename TipElemenata, typename FunTip>
TipElemenata Umotaj(const TipElemenata &kontejner, FunTip f) {
    // uklanjamo 'const' i 'reference' iz TipElemenata
    std::remove_cv_t<std::remove_reference_t<decltype(*kontejner.begin())>> v{};
    // drugi nacin:
    // using value_type = typename TipElemenata::value_type;
    // value_type v{};

    TipElemenata rezultat;

    for (const auto &e: kontejner) {
        v = f(v, e);
        rezultat.insert(rezultat.end(), v);
    }
    return rezultat;
}

int main() {
    std::cout << "Unesite 4 elementa skupa: ";
    std::set<int> skup;
    for (int i = 0; i < 4; i++) {
        int x;
        std::cin >> x;
        skup.insert(x);
    }

    std::set<int> novi_skup = Umotaj(skup, [](int x, int y) { return x * x + y * y; });

    std::cout << "Novi skup: ";
    for (int x: novi_skup) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
