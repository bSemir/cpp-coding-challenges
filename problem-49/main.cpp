#include <iostream>
#include <vector>
#include <stdexcept>


void AnalizaMatrice(std::vector<std::vector<double>> matrica, std::vector<int> &nul_redovi, std::vector<int> &nul_kolone) {
    nul_redovi.clear();
    nul_kolone.resize(0);
    for (int i = 0; i < matrica.size(); i++) {
        if (matrica[i].size() != matrica[0].size()) throw std::domain_error("Grbava matrica!");
        bool nul_red = true;
        for (int j = 0; j < matrica[i].size(); j++) {
            if (matrica[i][j] != 0) {
                nul_red = false;
                break;
            }
        }
        if (nul_red) nul_redovi.push_back(i);
    }

    for (int i = 0; i < matrica[0].size(); i++) { //
        bool nul_kolona = true;
        for (int j = 0; j < matrica.size(); j++) {
            if (matrica[j][i] != 0) {
                nul_kolona = false;
                break;
            }
        }
        if (nul_kolona) nul_kolone.push_back(i);
    }
}

int main() {
    try {
        std::cout << "Unesite dimenzije matrice: ";
        int m, n;
        std::cin >> m >> n;
        std::vector<std::vector<double>> mat(m, std::vector<double>(n));
        std::cout << "Unesite elemente: \n";
        for (auto &red: mat)
            for (double &el: red) std::cin >> el;

        std::vector<int> nul_redovi(m);
        std::vector<int> nul_kolone(mat.size());
        AnalizaMatrice(mat, nul_redovi, nul_kolone);
        std::cout << "Nul-redovi: ";
        for (const auto &e: nul_redovi) std::cout << e << " ";
        std::cout << std::endl;
        std::cout << "Nul-kolone: ";
        for (const auto &e: nul_kolone) std::cout << e << " ";
    } catch (const std::domain_error &err) {
        std::cout << "Izuzetak: " << err.what() << std::endl;
    }
    return 0;
}

// NOTE: if (std::count(matrica[i].begin(), matrica[i].end(), 0) == matrica[i].size()) nul_redovi.push_back(i);