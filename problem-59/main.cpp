#include <iostream>
#include <functional>
#include <memory>
#include <stdexcept>

std::unique_ptr<double[]> Tabeliraj(double xmin, double xmax, int n, std::function<double(double)> f) {
    if (n < 2 || xmin > xmax) throw std::domain_error("Neispravni parametri");
    double vel = (xmax - xmin) / (n - 1);

    auto niz = std::make_unique<double[]>(n);
    for (int i = 0; i < n; i++)
        niz[i] = f(xmin + i * vel);
    // WRONG: for(double x = xmin; x <= xmax; x += dx) pok_niz[i] = f(x);

    return niz;
}

int main() {
    try {
        std::cout << "Vrijednosti funkcije f(x)=x^3 za x od 0 do 5 s korakom 0.5: \n";
        auto pok_niz = Tabeliraj(0, 5, 11, [](double x) {
            return x * x * x;
        });
        for (int i = 0; i < 11; i++)
            std::cout << pok_niz[i] << " ";
    } catch (const std::domain_error &error) {
        std::cout << "Exception: " << error.what() << std::endl;
    }
    return 0;
}