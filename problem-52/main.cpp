#include <iostream>
#include <iomanip>

enum class NacinAlokacije {
    Fragmentirano, Kontinualno
};

int **TablicaMnozenja(int n, NacinAlokacije alokacija) {
    if (n <= 0) return nullptr;
    int **niz = nullptr;
    niz = new int *[n];
    for (int i = 1; i <= n; i++) niz[i] = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            niz[i][j] = i * j;
        }
    }
    return niz;
}

int main() {
    std::cout << "Unesite format tablice: ";
    int n;
    std::cin >> n;
    int **mat = TablicaMnozenja(n, NacinAlokacije::Fragmentirano);
    if (!mat) std::cout << "Neuspjesna alokacija!";
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << std::setw(4) << mat[i][j];
            }
            std::cout << std::endl;
        }
        for (int i = 0; i < n; i++) delete[] mat[i];
        delete[] mat;
    }
    return 0;
}
