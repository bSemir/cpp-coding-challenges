#include <iostream>
#include <vector>
#include <stdexcept>


template<typename IterTip1, typename IterTip2, typename FunTip>
auto GeneraliziraniSpoljasnjiProizvod(IterTip1 &a, IterTip2 &b, FunTip f) {
    // tip
    using T = std::remove_reference_t<decltype(f(*std::begin(a), *std::begin(b)))>;

    int m = 0; // a
    for (auto p = std::begin(a); p != std::end(a); p++) m++;
    int n = 0; // b
    for (auto p = std::begin(b); p != std::end(b); p++) n++;
    T **C = nullptr;

    try {
        C = new T *[m]; // alociramo niz od m pokazivaca na tip T jer je matrica dimenzija m x n
        C[0] = new T[m * n];
        for (int i = 1; i < m; i++) C[i] = C[i - 1] + n;
    } catch (...) {
        delete[] C;
        throw std::range_error("Nema dovoljno memorije");
    }
    auto it1 = std::begin(a); // it1 pokazuje na prvi element sekvence a
    for (int i = 0; i < m; i++) {
        auto it2 = std::begin(b);
        for (int j = 0; j < n; j++) {
            C[i][j] = f(*it1, *it2++);
        }
        it1++;
    }
    return C;
}

int main() {
    std::cout << "Unesite duzinu prve sekvence: ";
    int m;
    std::cin >> m;
    std::cout << "Elementi prve sekvence: ";
    std::vector<int> a(m);
    for (auto &el: a) std::cin >> el;

    std::cout << "Unesite duzinu druge sekvence: ";
    int n;
    std::cin >> n;
    std::cout << "Elementi druge sekvence: ";
    std::vector<int> b(n);
    for (auto &el: b) std::cin >> el;

    std::cout << "Generalizirani spoljasnji proizvod uz f(x,y)=x+2y: \n";
    try {
        auto C = GeneraliziraniSpoljasnjiProizvod(a, b, [=](int x, int y) {
            return x + 2 * y;
        });
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << C[i][j] << " ";
            }
            std::cout << std::endl;
        }
        delete[] C[0];
        delete[] C;
    } catch (std::exception &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    return 0;
}
