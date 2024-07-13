#include <iostream>
#include <array>
#include <iterator>

template<typename tip1, typename tip2>
tip2 podblok(tip1 pocetak1, tip1 kraj1, tip2 pocetak2, tip2 kraj2) {
    if (pocetak2 == kraj2) return pocetak1; // prazan podblok
    while (pocetak1 != kraj1) {
        auto it1 = pocetak1;
        auto it2 = pocetak2;
        while (it1 != kraj1 && it2 != kraj2 && *it1 == *it2) {
            ++it1;
            ++it2;
        }
        if (it2 == kraj2) return pocetak1; // pronadjen podblok
        ++pocetak1;
    }
    return kraj1; // nije pronadjen podblok
}

int main() {
    std::array<int, 6> niz1{1, 7, 3, 5, 2, 6};
    std::array<int, 3> niz2{3, 5, 2};
    std::cout << "Drugi niz se ";
    if (podblok(niz1.begin(), niz1.end(), niz2.begin(), niz2.end()) == niz1.end())
        std::cout << "ne ";
    std::cout << "nalazi kao podblok u prvom nizu!";
    return 0;
}