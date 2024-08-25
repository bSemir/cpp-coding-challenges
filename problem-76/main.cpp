#include <iostream>
#include <list>

template<typename IterTip1, typename IterTip2, typename FunTip>
auto
GeneraliziraniSkalarniProdukt(IterTip1 pocetak_prve, IterTip1 kraj_prve, IterTip2 pocetak_druge, FunTip f) {
    using tip = std::remove_reference_t<decltype(f(*pocetak_prve, *pocetak_druge))>;
    tip result{};
    while (pocetak_prve != kraj_prve)
        result += f(*pocetak_prve++, *pocetak_druge++);
    return result;
}

int main() {
    std::cout << "Duzina sekvenci: ";
    int n;
    std::cin >> n;

    std::cout << "Unesite prvu sekvencu: ";
    std::list<double> v1(n);
    for (auto &e: v1) std::cin >> e;
    std::list<double> v2(n);

    std::cout << "Unesite drugu sekvencu: ";
    for (auto &e: v2) std::cin >> e;

    auto p = GeneraliziraniSkalarniProdukt(v1.begin(), v1.end(), v2.begin(), [=](auto x, auto y) {
        return x * y;
    });
    std::cout << "Skalarni produkt: " << p << std::endl;
    return 0;
}