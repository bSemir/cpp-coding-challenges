#include <iostream>
#include <vector>

std::vector<int> izdvoji_cifre(int n) {
    std::vector<int> cifre;
    while (n > 0) {
        cifre.push_back(n % 10);
        n /= 10;
    }
    return cifre;

}

bool sadrze_istu_cifru(int &p, int &q) {
    auto cifre_p = izdvoji_cifre(p);
    auto cifre_q = izdvoji_cifre(q);
    for (auto cifra_p: cifre_p) {
        for (auto cifra_q: cifre_q) {
            if (cifra_p == cifra_q)
                return true;
        }
    }
    return false;
}

int main() {
    std::cout << "Unesite brojeve p i q: ";
    int p, q;
    std::cin >> p >> q;
    if (sadrze_istu_cifru(p, q))
        std::cout << "Brojevi " << p << " i " << q << " sadrze istu cifru." << std::endl;
    else
        std::cout << "Brojevi " << p << " i " << q << " ne sadrze istu cifru." << std::endl;
    return 0;
}
