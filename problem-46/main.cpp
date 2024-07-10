#include <iostream>
#include <vector>
#include <stdexcept>

enum class VrstaNiza {
    Aritmeticki, Geometrijski, Nespecificni
};

VrstaNiza vrati_tip_niza(const std::vector<int> &v) {
    if (v.empty()) throw std::logic_error("Empty vector!");
    if (v.size() < 2) return VrstaNiza::Nespecificni;
    bool a = true;
    int razlika = v[0] - v[1]; // profesor je radio v[1] - v[0]
    for (int i = 0; i < v.size() - 1; i++) // i ovdje isao od 2 do size
        if (v[i] - v[i + 1] != razlika) a = false;
    int kolicnik = v[0] / v[1];
    bool g = true;
    for (int i = 0; i < v.size() - 1; i++)
        if (v[i] / v[i + 1] != kolicnik) g = false;
    if (a) return VrstaNiza::Aritmeticki;
    else if (g) return VrstaNiza::Geometrijski;
    else return VrstaNiza::Nespecificni;
}

int main() {
    std::cout << "Unesite broj elemenata: ";
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Unesite niz cijelih brojeva: ";
    for (auto &x: v) std::cin >> x;
    std::string tipovi[3]{"Aritmeticki", "Geometrijski", "Nespecificni"};
    std::cout << "Niz je: " << tipovi[int(vrati_tip_niza(v))];
    return 0;
}