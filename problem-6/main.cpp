#include <iostream>
#include <limits>
#include <vector>
#include <stdexcept>

void Minimax(const std::vector<std::vector<double>> &v, double &minimax, double &maximin);

int main() {
    std::vector<std::vector<double>> v = {{2, 6, 3, 1, 7}, {5, 2, 4, 8, 6}, {0, 7, 5, 4, 3}};
    double p, q;
    try {
        Minimax(v, p, q);
        std::cout << "Minimax vrijednost po redovima: " << p << '\n';
        std::cout << "Maximin vrijednost po redovima: " << q << '\n';
    } catch (const std::domain_error &e) {
        std::cout << e.what();
    }
    return 0;
}

void Minimax(const std::vector<std::vector<double>> &v, double &minimax, double &maximin) {
    if (v.empty())
        throw std::domain_error("Parametar nema formu matrice");

    minimax = std::numeric_limits<double>::max();
    maximin = std::numeric_limits<double>::min();
    for (auto red : v) {
        if (red.size() != v[0].size())  throw std::domain_error("Parametar nema formu matrice");
        if (red.empty()) throw std::domain_error("Neispravna matrica");
        double max_reda = red[0], min_reda = red[0];
        for (double el : red) {
            if(el > max_reda) max_reda = el;
            if(el < min_reda) min_reda = el;
        }
        if(max_reda < minimax) minimax = max_reda;
        if(min_reda > maximin) maximin = min_reda;
    }
}