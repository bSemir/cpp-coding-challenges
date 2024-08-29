#include <iostream>
#include <vector>

int izvrni_cifre(int n) {
    if (n == 0) return 0;
    bool negativan = n < 0;
    std::string s = "";
    while (n != 0) {
        auto c = std::to_string(std::abs(n % 10));
        std::string str{c};
        s += str;
        n /= 10;
    }
    int x = std::stoi(s);
    if (negativan)
        return -x;
    return x;
}

std::vector<int> SlikeUOgledalu(const std::vector<int> &v) {
    std::vector<int> vec;
    for (int i = 0; i < v.size(); i++) {
        int izvrnuti = izvrni_cifre(v.at(i));
        vec.push_back(izvrnuti); // vec.push_back(izvrni_cifre(v.at(i)));
    }
    return vec;
}

int main() {
    std::vector<int> v;
    std::cout << "Unesite element po element (0 za kraj): \n";
    int n;
    do {
        std::cout << "Element: ";
        std::cin >> n;
        if (n == 0) break;
        v.push_back(n);
    } while (n != 0);
    auto vec = SlikeUOgledalu(v);
    for (int i = 0; i < v.size(); i++)
        std::cout << "Slika u ogledalu broja " << v[i] << " glasi " << vec[i] << std::endl;
    return 0;
}