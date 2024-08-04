#include <iostream>
#include <vector>
#include <complex>

template<typename tip>
void f(const std::vector<std::vector<tip>> &m, std::vector<std::complex<double>> &v_max, std::vector<std::complex<double>> &v_min) {
    // TODO: implement this function
}

int main() {
    std::vector<std::vector<double>> m(5, std::vector<double>(5)); // 5x5 matrica
    std::cout << "Unesite matricu 5x5: ";
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            std::cin >> m[i][j];

    std::vector<std::complex<double>> v_max(5), v_min(5);
    f(m, v_max, v_min);
    return 0;
}

// NOTE: ako matrica moze biti grbava, C-ovske matrice ne dolaze u obzir!