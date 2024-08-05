#include <iostream>
#include <vector>
#include <complex>


template<typename tip>
void f(const std::vector<std::vector<tip>> &m, std::vector<std::complex<double>> &v_max,
       std::vector<std::complex<double>> &v_min) {
    tip max{}, min{};
    for (auto &row: m) {
        if (!row.empty()) {
            max = row[0];
            min = row[0];
            break;
        }
    }
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            if (m[i][j] > max) max = m[i][j];
            if (m[i][j] < min) min = m[i][j];
        }
    }

    v_max.clear();
    v_min.clear();
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m[i].size(); j++) {
            if (m[i][j] == max)
                v_max.push_back({static_cast<double>(i), static_cast<double>(j)});
            if (m[i][j] == min)
                v_min.push_back({static_cast<double>(i), static_cast<double>(j)});
        }
    }
}

int main() {
    std::vector<std::vector<double>> m(5, std::vector<double>(5)); // 5x5 matrica
    std::cout << "Unesite matricu 5x5: ";
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            std::cin >> m[i][j];

    std::vector<std::complex<double>> v_max, v_min;
    f(m, v_max, v_min);

    for (int i = 0; i < v_max.size(); i++)
        std::cout << "Max: " << v_max[i] << std::endl;
    for (int i = 0; i < v_min.size(); i++)
        std::cout << "Min: " << v_min[i] << std::endl;
    return 0;
}

//  test
//  1 2 3 4 5
//  4 3 2.2 99 105.1
//  11.12 21 11.13 88 0
//  8 6 3 77.77 77.78
//  5 4 3 105.1 105.1