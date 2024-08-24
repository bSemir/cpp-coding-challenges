#include <iostream>
#include <vector>
#include <algorithm>

int NZD(const std::vector<int> &v) {
    if (v.empty()) return -1;
    int najmanji = *std::min_element(v.begin(), v.end());
    for (int i = najmanji; i > 0; i--) {
        bool djeljiv = true;
        for (int j = 0; j < v.size(); j++) {
            if (v[j] % i != 0) {djeljiv = false;
            break;
            }
        }
        if (djeljiv) return i;
    }
    return 1;
}

int main() {
    std::vector<int> v{305, 5630, 210, 8470, 7305};
    if (NZD(v) != -1) std::cout << "NZD: " << NZD(v) << std::endl;
    else std::cout << "Greska ili je rezultat 1\n";
    return 0;
}