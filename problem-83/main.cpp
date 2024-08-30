#include <iostream>
#include <list>

int suma_djelilaca(int x);

template<typename IterTip, typename FunTip>
IterTip max_element_custom(IterTip pocetak, IterTip kraj, FunTip f) {
    IterTip max = pocetak;
    ++pocetak;
    while (pocetak++ != kraj) {
        if (f(*max, *pocetak))
            max = pocetak;
    }
    return max;
}

int suma_djelilaca(int x) {
    int s = 0;
    for (int i = 1; i <= x; i++)
        if (x % i == 0) s += i;
    return s;
    return 0;
}

int main() {
    std::list<int> l(10);
    std::cout << "Unesite 10 elemenata u listu:\n";
    for (int i = 0; i < 10; i++) {
        int b;
        std::cin >> b;
        l.push_back(b);
    }
    auto max = max_element_custom(l.begin(), l.end(), [](int x, int y) {
        return suma_djelilaca(x) < suma_djelilaca(y);
    });
    std::cout << "Max element je: " << *max << std::endl;
    return 0;
}