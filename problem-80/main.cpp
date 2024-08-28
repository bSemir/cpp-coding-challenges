#include <iostream>
#include <stdexcept>

template<typename tip>
void KreirajMatricu(tip **&A, int br_redova, int br_kolona, bool nacin = true, tip vrijednost = {}) {
    A = nullptr;
    try {
        if (nacin) {
            // kontinualna
            A = new int *[br_redova]{};
            A[0] = new int[br_redova * br_kolona];
            // postavljanje pokazivaca da pokazuju na pocetke odg redovak
            for (int i = 1; i < br_redova; i++) A[i] = A[i - 1] + br_kolona;
            // popunjavanje
            for (int i = 0; i < br_redova; i++) {
                for (int j = 0; j < br_kolona; j++) {
                    A[i][j] = vrijednost;
                }
            }
        } else {
            // fragmentirana
            A = new int *[br_redova]{};
            // postavljanje pokazivaca
            for (int i = 0; i < br_redova; i++) A[i] = new int[br_kolona];
            // popunjavanje
            for (int i = 0; i < br_redova; i++) {
                for (int j = 0; j < br_kolona; j++) {
                    A[i][j] = vrijednost;
                }
            }
        }
    } catch (...) {
        if (!nacin)
            for (int i = 0; i < br_redova; i++) delete A[i];
        delete[] A;
        throw;
    }
}

template<typename T>
T **KreirajMatricu(int br_redova, int br_kolona, bool nacin = true, T inicijalna_vrijednost = {}) {
    T **A = nullptr;
    KreirajMatricu(A, br_redova, br_kolona, nacin, inicijalna_vrijednost);
    return A;
}

int main() {
    std::cout << "Unesite broj redova i kolona matrice: ";
    int br_redova, br_kolona;
    std::cin >> br_redova >> br_kolona;
    if (br_redova <= 0 || br_kolona <= 0) {
        std::cout << "Unijeli ste pogresne dimenzije redova i/ili kolona!";
        return 0;
    }
    std::cout << "Unesite nacin alokacije(1 - Kontinualno, 2 - Fragmentirano): ";
    int x;
    std::cin >> x;
    bool nacin;
    if (x == 1) nacin = true;
    else nacin = false;
    std::cout << "Unesite vrijednost s kojom ce matrica biti popunjena(int): ";
    int vrijednost;
    std::cin >> vrijednost;

    int **A;
    try {
        KreirajMatricu(A, br_redova, br_kolona, nacin);
        std::cout << "👇 Kreirana matrica 👇\n";
        for (int i = 0; i < br_redova; i++) {
            for (int j = 0; j < br_kolona; j++) {
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }
    } catch (std::exception &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    return 0;
}