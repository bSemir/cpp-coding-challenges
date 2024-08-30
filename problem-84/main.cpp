#include <iostream>
#include <vector>
#include <deque>
#include <type_traits>


template<typename tip1, typename tip2>
auto ZbirKontejnera(const tip1 &c1, const tip2 &c2) {
    using T = std::remove_reference_t<decltype(*std::begin(c1) + *std::begin(c2))>;
    int size_1 = std::distance(std::begin(c1), std::end(c1));
    int size_2 = std::distance(std::begin(c2), std::end(c2));
    int vel = std::max(size_1, size_2);
    std::vector<T> C(vel);
    auto it = std::begin(C);

    auto p1 = std::begin(c1);
    auto p2 = std::begin(c2);

    if (size_1 > size_2) {
        for (int i = 0; i < size_2; i++)
            *it++ = *p1++ + *p2++;
        for (int i = 0; i < size_1 - size_2; i++)
            *it++ = *p1++;
    } else if (size_1 == size_2) {
        for (int i = 0; i < size_1; i++)
            *it++ = *p1++ + *p2++;
    } else {
        for (int i = 0; i < size_1; i++)
            *it++ = *p1++ + *p2++;
        for (int i = 0; i < size_2 - size_1; i++)
            *it++ = *p2++;
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