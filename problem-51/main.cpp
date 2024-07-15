#include <iostream>
#include <algorithm>
#include <vector>
#include <type_traits>

template<typename T>
auto suma_elemenata_reda(std::vector<T> &red) {
    T suma{};
//    std::remove_reference<decltype(red[0])> suma{};
    for (const T &e: red) {
        suma += e;
    }
    return suma;
}

template<typename T>
void SortirajMatricu(std::vector<std::vector<T>> &m) {
    std::sort(m.begin(), m.end(), [](std::vector<T> &v1, std::vector<T> &v2) {
//        std::remove_reference<decltype(v1[0])> suma_prvog{}, suma_drugog{};
        auto s1 = suma_elemenata_reda(v1);
        auto s2 = suma_elemenata_reda(v2);
        if (s1 != s2) return s1 < s2;
        if (v1.size() != v2.size()) return v1.size() < v2.size();
        return v1 < v2;
    });
}

int main() {
    std::cout << "Unesite dimenzije: ";
    int m, n;
    std::cin >> m >> n;
    std::cout << "Unesite elemente:\n";
    std::vector<std::vector<double>> mat(m, std::vector<double>(n));
    for (auto &red: mat) {
        for (auto &el: red)
            std::cin >> el;
    }
    std::cout << "Matrica nakon sortiranja:\n";
    SortirajMatricu(mat);
    for (auto &red: mat) {
        for (auto &el: red)
            std::cout << el << " ";
        std::cout << std::endl;
    }
    return 0;
}