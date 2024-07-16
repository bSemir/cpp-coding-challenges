#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <stdexcept>


template<typename tip>
auto **kompaktifikacija_matrice(tip **a, int m, int n) {
    using TipElemenata = std::remove_reference_t<decltype(a[0][0])>;
    TipElemenata **matrica{};

    try {
        matrica = new tip *[m];
        matrica[0] = new tip[m * n];
        for (int i = 0; i < m; i++) {
            if (i != 0) matrica[i] = matrica[i - 1] + n;
            // for (int j = 0; j < n; j++) matrica[i][j] = a[i][j];
            std::copy(a[i], a[i] + n, matrica[i]);
        }
        for (int i = 0; i < m; i++) delete[] a[i];
        delete[] a;
        a = matrica;
    } catch (...) {
        delete[] matrica[0];
        throw std::domain_error("Problemi sa alokacijom!");
    }

    return a;
}

// helper
int **alociraj_fragmentirano(std::vector<std::vector<int>> &v) {
    int **m{};
    try {
        m = new int *[v.size()];
        for (int i = 0; i < v.size(); i++) {
            m[i] = new int[v[i].size()];
            std::copy(v[i].begin(), v[i].end(), m[i]);
        }
    } catch (...) {
        for (int i = 0; i < v.size(); i++) delete[] m[i];
        delete[]m;
        throw std::domain_error("Neuspjesna fragmentirana alokacija");
    }
    return m;
}

int main() {
    std::cout << "Unesite dimenzije matrice (m i n): ";
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int>> v(m, std::vector<int>(n));
    std::cout << "Unesite elemente: \n";
    for (auto &red: v) {
        for (auto &el: red) std::cin >> el;
    }

    int **mat = alociraj_fragmentirano(v);
    std::cout << "Fragmentirano: \n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }

    int **k_matrica = kompaktifikacija_matrice<int>(mat, m, n);
    std::cout << "Kompaktifikovano: \n";
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << k_matrica[i][j] << " ";
        }
        std::cout << std::endl;
    }

//    for (int i = 0; i < m; i++) delete[] mat[i];
//    delete[] mat;
    delete[] k_matrica[0];
    return 0;
}

/*
Primjer interakcije programa i korisnika:

Unesite dimenzije matrice (m i n): 4 6
Unesite elemente:
2 5 3 7 4 1
0 4 2 3 9 5
6 3 2 4 3 0
0 0 5 9 7 6
Fragmentirano:
2 5 3 7 4 1
0 4 2 3 9 5
6 3 2 4 3 0
0 0 5 9 7 6
Kompaktifikovano:
2 5 3 7 4 1
0 4 2 3 9 5
6 3 2 4 3 0
0 0 5 9 7 6
*/