#include <iostream>
#include <vector>
#include <deque>
#include <type_traits>


template<typename tip1, typename tip2>
auto ZbirKontejnera(const tip1 &c1, const tip2 &c2) {
    using T = std::remove_reference_t<decltype(*std::begin(c1) + *std::begin(c2))>;
//    int size_1 = std::distance(std::begin(c1), std::end(c1));
//    int size_2 = std::distance(std::begin(c2), std::end(c2));
//    int vel = std::max(size_1, size_2);
    std::vector<T> C;
//    auto it = std::begin(C);

    auto p1 = std::begin(c1);
    auto p2 = std::begin(c2);

    using TipElemenata1 = std::remove_reference_t<decltype(*p1 + *p1)>;
    using TipElemenata2 = std::remove_reference_t<decltype(*p2 + *p2)>;

//    if (size_1 > size_2) {
//        for (int i = 0; i < size_2; i++)
//            *it++ = *p1++ + *p2++;
//        for (int i = 0; i < size_1 - size_2; i++)
//            *it++ = *p1++;
//    } else if (size_1 == size_2) {
//        for (int i = 0; i < size_1; i++)
//            *it++ = *p1++ + *p2++;
//    } else {
//        for (int i = 0; i < size_1; i++)
//            *it++ = *p1++ + *p2++;
//        for (int i = 0; i < size_2 - size_1; i++)
//            *it++ = *p2++;
//    }

// IMPORTANT
    while (p1 != std::end(c1) || p2 != std::end(c2)) {
        TipElemenata1 e1;
        if (p1 != std::end(c1)) {
            e1 = *p1;
            ++p1;
        } else {
            e1 = TipElemenata1(); // podrazumijevana vrijednost
        }
        TipElemenata2 e2;
        if (p2 != std::end(c2)) {
            e2 = *p2;
            ++p2;
        } else {
            e2 = TipElemenata2();
        }
        C.push_back(e1 + e2);
    }
    return C;
}

int main() {
    std::cout << "Duzina prvog kontejnera: ";
    int dp;
    std::cin >> dp;
    std::cout << "Elementi prvog kontejnera: ";
    std::vector<double> v1(dp);
    for (auto &el: v1) std::cin >> el;

    std::cout << "Duzina drugog kontejnera: ";
    int dd;
    std::cin >> dd;
    std::cout << "Elementi drugog kontejnera: ";
    std::vector<double> v2(dd);
    for (auto &el: v2) std::cin >> el;

    std::cout << "Zbir kontejnera: ";
    auto v = ZbirKontejnera(v1, v2);
    for (int i = 0; i < v.size(); i++)
        std::cout << v.at(i) << " ";
    return 0;
}