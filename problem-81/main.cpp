#include <iostream>
#include <vector>
#include <stdexcept>

// kontinualna

template<typename IterTip1, typename IterTip2, typename FunTip>
auto GeneraliziraniSpoljasnjiProizvod(IterTip1 &a, IterTip2 &b, FunTip f) {
    // tip
    using T = std::remove_reference_t<decltype(f(*std::begin(a), std::begin(b)))>;
    // broj redova
//    int br_redova_a = 0;
//    for (auto p = std::begin(a); p != std::end(a); p++) br_redova_a++;
//    int br_redova_b = 0;
//    for (auto p = std::begin(b); p != std::end(b); p++) br_redova_b++;
//    int br_redova;
//    if (br_redova_a > br_redova_b)
//        br_redova = br_redova_a;
//    else br_redova = br_redova_b;
//
    int m = 0; // a
    for (auto p = std::begin(a); p != std::end(a); p++) m++;
    int n = 0; // b
    for (auto p = std::begin(b); p != std::end(b); p++) n++;
    T **C = nullptr;

    try {
        C = new T *[m];
        C[0] = new T[m * n];
        for (int i = 1; i < m; i++) C[i] = C[i - 1] + n;
    } catch (...) {
        delete[] C;
        throw std::range_error("Nema dovoljno memorije");
    }
    auto it1 = std::begin(a);
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
    
    return 0;
}
