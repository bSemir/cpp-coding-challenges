#include <iostream>
#include <vector>
#include <stdexcept>
#include <valarray>


int suma_stepeni_cifara(int n, int i) {
    int s = 0;
    while (n != 0) {
        s += std::pow(std::abs(n % 10), i);
        n /= 10;
    }
    return s;
}

int **f(std::vector<int> &v, int n) {
    if (n <= 0) throw std::range_error("Pogresan broj redova matrice");

    using tip = std::remove_reference_t<decltype(v[0])>;

    int m = v.size();
    tip **mat{};
    try {
        mat = new tip *[n]{}; // niz pokazivaca!
        mat[0] = new tip[m * n];
        for (int i = 0; i < n; i++) {
            if (i != 0) mat[i] = mat[i - 1] + m;
            std::copy(v.begin(), v.end(), mat[i]);
            std::sort(mat[i], mat[i] + m, [=](auto x, auto y) {
                int s1 = suma_stepeni_cifara(x, i);
                int s2 = suma_stepeni_cifara(y, i);
                if (s1 != s2) return s1 < s2;
                return x < y;
            });
        }
    } catch (...) {
        delete[] mat;
        throw std::range_error("Problemi s alokacijom!");
    }
    return mat;
}

int main() {
    std::cout << "Unesite 5 cijelih brojeva: ";
    int n = 3;
    std::vector<int> v(5);
    for (auto &el: v) std::cin >> el;

    int **niz = f(v, n);
    std::cout << "👇\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < v.size(); j++) {
            std::cout << niz[i][j] << " ";
        }
        std::cout << std::endl;
    }
    delete[] niz[0];
    delete[] niz;

    return 0;
}