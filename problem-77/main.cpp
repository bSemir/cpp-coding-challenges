#include <iostream>
#include <vector>

void DodajSuprotne(std::vector<int> &v) {
    if (v.empty()) return;
    for (int i = 0; i < v.size(); i++) {
        v.insert(v.begin() + 1 + i, -v.at(i));
        i++; // IMPORTANT! Skip over the element we've just inserted
    }
}

int main() {
    std::cout << "Koliko ima brojeva: ";
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Unesite brojeve: ";
    for (auto &e: v) std::cin >> e;

    DodajSuprotne(v);
    for (int i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    return 0;
}