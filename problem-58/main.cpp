#include <iostream>
#include <list>
#include <iterator>

int broj_cifara(int b) {
    int res = 0;
    while (b != 0) {
        b /= 10;
        res++;
    }
    return res;
}

template<typename IterTip1, typename IterTip2, typename FunkTip>
IterTip2 KopirajUzUvjetnoUklanjanje(IterTip1 pocetak, IterTip1 kraj, IterTip2 odrediste, FunkTip f) {
    while (pocetak != kraj) {
        if (!f(*pocetak)) {
            *odrediste = *pocetak;
            odrediste++;
            pocetak++;
        } else pocetak++;
    }
    return odrediste;
    // works also
    // for (; pocetak != kraj; pocetak++)
    //    if (!f(*pocetak)) *odrediste++ = *pocetak;
    // return odrediste;
}

int main() {
    std::cout << "Unesite 5 brojeva: ";
    std::list<int> lista(5);
    for (auto &e: lista) std::cin >> e;
    std::cout << "Unesite dozvoljeni broj cifara: ";
    int c;
    std::cin >> c;
    std::list<int> nova(5);
    auto x = KopirajUzUvjetnoUklanjanje(lista.begin(), lista.end(), nova.begin(), [=](auto e1) {
        if (broj_cifara(e1) > c) return true;
        return false;
    });

    int duzina = std::distance(nova.begin(), x);
    nova.resize(duzina);
    std::cout << "Preostali brojevi: ";
    for (int el: nova) std::cout << el << " ";

    return 0;
}