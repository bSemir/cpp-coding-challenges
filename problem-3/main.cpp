#include <iostream>
#include <vector>
#include <cmath>

bool DaLiJeProst(int number);
std::vector<int>ProstiBrojeviUOpsegu(int a, int b);

int main() {
    std::cout << "Unesite pocetnu i krajnju vrijednost: ";
    int a, b;
    std::cin >> a >> b;
    std::vector<int> v = ProstiBrojeviUOpsegu(a, b);
    if (v.size() > 1) {
        std::cout << "Prosti brojevi u opsegu od " << a << " do " << b << " su: ";
        for(int i = 0; i < v.size(); i++) {
            std::cout << v.at(i);
            if (i != v.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Nema prostih brojeva u opsegu od " << a << " do " << b << std::endl;
    }
    return 0;
}

bool DaLiJeProst(int number) {
    if (number < 2) return false;
    int root = int(sqrt(number));
    for(int i = 2; i <= root; i++)
        if (number % i == 0) return false;
    return true;
}

std::vector<int>ProstiBrojeviUOpsegu(int a, int b) {
    std::vector<int> primes;
    for(int i = a; i <= b; i++) {
        if (DaLiJeProst(i)) primes.push_back(i);
        if (i == b) break; // prevent overflow, INT_MAX
    }
    return primes;
}