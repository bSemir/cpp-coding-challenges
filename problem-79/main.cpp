#include <iostream>
#include <stdexcept>

void KreirajPascalovTrougao(int **&A, int n) {
    if (n <= 0) throw std::domain_error("Pogresan broj redova");
    A = nullptr;
    try {
        A = new int *[n];
        A[0] = new int[n * (n + 1) / 2]; // jedan niz s ukupnim brojem elemenata na koji pokazuje prvi pokazivac
    } catch (...) {
        delete[] A;
        throw std::range_error("Kreiranje nije uspjelo");
    }
    for (int i = 1; i < n; i++) A[i] = A[i - 1] + i; // postavljanje pokazivaca(svaki red ima `i` elemenata)
    // popunjavanje matrice
    for (int i = 0; i < n; i++) {
        A[i][0] = A[i][i] = 1;
        for (int j = 1; j < i; j++) A[i][j] = A[i - 1][j] + A[i - 1][j - 1];
    }
}

int main() {
    std::cout << "Unesite broj redova: ";
    int n;
    std::cin >> n;
    int **A;
    try {
        KreirajPascalovTrougao(A, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
        delete[] A[0];
        delete[] A;
    } catch (std::exception &e) {
        std::cout << "Problem: " << e.what() << "!" << std::endl;
    }
    return 0;
}