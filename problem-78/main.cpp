#include <iostream>
#include <stdexcept>

int **KreirajTrougao(int n) {
    if (n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");

    int **matrica = nullptr;
    try {
        matrica = new int *[n];
        // alokacija redova
        for (int i = 0; i < n; i++)
            matrica[i] = new int[2 * i + 1];
        // popunjavanje
        for (int i = 0; i < n; i++) {
            // int x = i + 1;
            for (int j = 0; j < i; j++) matrica[i][j] = i + 1 - j;
            for (int k = i; k <= 2 * i + 1; k++) matrica[i][k] = k + 1 - i;

        }
    } catch (...) {
        for (int i = 0; i < n; i++) delete[] matrica[i];
        delete[] matrica;
        throw;
    }
    return matrica;
}

int main() {
    std::cout << "Koliko zelite redova: ";
    int n;
    std::cin >> n;
    try {
        auto mat = KreirajTrougao(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2 * i + 1; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << "\n";
        }
        for (int i = 0; i < n; i++) delete mat[i];
        delete[] mat;
    } catch (std::exception &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    return 0;
}
