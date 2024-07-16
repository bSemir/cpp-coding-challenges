#include <iostream>
#include <vector>
#include <stdexcept>


int suma_stepeni_cifara(std::vector<int> v, int i) {
    //TODO
}

int **f(std::vector<int> &v, int n) {
    if (n <= 0) throw std::range_error("Pogresan broj redova matrice");

    using tip = std::remove_reference_t<decltype(v[0])>;

    int m = v.size();
    tip **mat{};
    try {
        mat = new tip *[n];
        mat[0] = new tip[m * n];
        for (int i = 0; i < n; i++) {
            if (i != 0) mat[i] = mat[i - 1] + m;
            // TODO: copy and sort elements
        }
    } catch (...) {
        delete[] mat;
        throw std::range_error("Problemi s alokacijom!");
    }
    return mat;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
