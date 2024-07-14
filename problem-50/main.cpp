#include <iostream>
#include <vector>
#include <algorithm>

enum class Smjer {
    Nalijevo, Nadesno
};

bool grbava(std::vector<std::vector<double>> &m) {
    if (m.size() == 0) return false;
    int n = m[0].size();
    for (int i = 1; i < m.size(); i++) if (m[i].size() != n) return true;
    return false;
}

void Iskosi(std::vector<std::vector<double>> &m, Smjer smjer) {
    if (grbava(m)) throw std::domain_error("Grbava matrica");
    int n = m.size(); // broj redova
    for (int i = 0; i < n; i++) {
        if (smjer == Smjer::Nalijevo) {
            m[i].resize(m.size() - 1 + m[i].size());
            int pomak = i; // pomak za i mjesta u lijevo (i je redni broj reda)
            std::copy_backward(m[i].begin(), m[i].end() - m.size() + 1, m[i].end() - m.size() + 1 + pomak);
            std::fill(m[i].begin(), m[i].begin() + pomak, 0);
        } else {
            m[i].resize(m.size() - 1 + m[i].size());
            int pomak = n - 1 - i; // pomak za n - 1 - i mjesta u desno
            std::copy_backward(m[i].begin(), m[i].end() - m.size() + 1, m[i].end() - m.size() + 1 + pomak);
            std::fill(m[i].end() - pomak, m[i].end(), 0);
        }
    }
}

int main() {
    try {
        std::cout << "Unesite dimenzije matrice (m n): ";
        int m, n;
        std::cin >> m >> n;
        if (m <= 0 || n <= 0) {
            std::cout << "Dimenzije matrice moraju biti prirodni brojevi.";
            return 0;
        }
        std::vector<std::vector<double>> matrica(m, std::vector<double>(n));
        std::cout << "Unesite elemente matrice: \n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) std::cin >> matrica[i][j];
        }

        Iskosi(matrica, Smjer::Nalijevo);
        std::cout << "Lijevo iskosenje: \n";
        for (int i = 0; i < matrica.size(); i++) {
            for (int j = 0; j < matrica[i].size(); j++) std::cout << matrica[i][j] << " ";
            std::cout << std::endl;
        }
        std::cout << "Desno iskosenje: \n";
        Iskosi(matrica, Smjer::Nadesno);
        for (int i = 0; i < matrica.size(); i++) {
            for (int j = 0; j < matrica[i].size(); j++) std::cout << matrica[i][j] << " ";
            std::cout << std::endl;
        }
    } catch (std::domain_error e) {
        std::cout << e.what();
    }
    return 0;
}