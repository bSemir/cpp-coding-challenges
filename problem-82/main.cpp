#include <iostream>
#include <vector>
#include <string>


int izvrni_cifre(int n) {
    if (n == 0) return 0;
    bool negativan = n < 0;
    std::string s = std::to_string(n);
    std::reverse(s.begin(), s.end());
    int x = std::stoi(s);
    return negativan ? -x : x;
}

std::vector<int> SlikeUOgledalu(const std::vector<int> &v) {
    std::vector<int> vec;
    for (auto &n: v)
        vec.push_back(izvrni_cifre(n));
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