#include <iostream>
#include <stdexcept>

// Fragmentirana alokacija
int **KreirajTrougaoFragmentirano(int n) {
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

// Kontinualna alokacija
int **KreirajTrougaoKontinualno(int n) {
    if (n <= 0) throw std::domain_error("Broj redova mora biti pozitivan");

    int **matrica{};
    try {
        matrica = new int *[n]{}; // niz od `n` pokazivaca
        matrica[0] = new int[n * n]; // prvi pokazivac pokazuje na niz velicine `n*n` koji je dovoljan
        for (int i = 1; i < n; i++)
            matrica[i] = matrica[i - 1] + 2 * i + 1; // postavljanje pokazivaca na pocetke redova
        // popunjavanje
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++)
                matrica[i][j] = i + 1 - j;
            for (int k = i; k <= 2 * i + 1; k++)
                matrica[i][k] = k + 1 - i;
        }
    } catch (...) {
        delete[] matrica;
        throw;
    }
    return matrica;
}

int main() {
    std::cout << "Koliko zelite redova: ";
    int n;
    std::cin >> n;
//    try {
//        auto mat = KreirajTrougaoFragmentirano(n);
//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < 2 * i + 1; j++) {
//                std::cout << mat[i][j] << " ";
//            }
//            std::cout << "\n";
//        }
//        for (int i = 0; i < n; i++) delete mat[i];
//        delete[] mat;
//    } catch (std::exception &e) {
//        std::cout << "Izuzetak: " << e.what() << std::endl;
//    }
    try {
        auto mat = KreirajTrougaoKontinualno(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 2 * i + 1; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << "\n";
        }
        delete[] mat[0]; delete[] mat;
    } catch (std::exception &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    return 0;
}