#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int NZD(const std::vector<int> &v) {
    if (v.empty()) return 0;
//    int najmanji = *std::min_element(v.begin(), v.end()); //
    int najveci = *std::max_element(v.begin(), v.end(), [](int x, int y) {
        return std::abs(x) < std::abs(y);
    });
    if (najveci == 0) return 0;
    for (int i = najveci; i > 0; i--) {
        bool djeljiv = true;
        for (int j: v) {
            if (j % i != 0) {
                djeljiv = false;
                break;
            }
        }
        if (djeljiv) return i;
    }
    return 1;
}

int main() {
    std::vector<int> v{135, -420, 0, 210, 840, -735};
    if (NZD(v) != 0) std::cout << "NZD: " << NZD(v) << std::endl;
    else std::cout << "Greska ili je rezultat 0\n";
    return 0;
}