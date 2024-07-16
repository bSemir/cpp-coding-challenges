#include <iostream>
#include <algorithm>
#include <stdexcept>


char **alokacija(int n) {
    if (n <= 0) throw std::range_error("Pogresan parametar");

    char **prva{};
    try {
        prva = new char *[n];
        for (int i = 0; i < n; i++) {
            prva[i] = new char[i + 1];
            std::fill(prva[i], prva[i] + 1 + i, '*');
        }
    } catch (...) {
        for (int i = 0; i < n; i++) delete[] prva[i];
        delete[] prva;
        throw std::range_error("Kreiranje nije uspjelo!");
    }
    return prva;
}

int main() {
    try {
        std::cout << "Unesite n: ";
        int n;
        std::cin >> n;
        char **mat = alokacija(n);
        if (!mat) std::cout << "Neuspjesna alokacija!";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i + 1; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
//        for (int i = 0; i < n; i++) delete[] mat[i];
//        delete[]mat;
    } catch (const std::range_error &e) {
        std::cout << "Exception: " << e.what() << std::endl;

    }

    return 0;
}
