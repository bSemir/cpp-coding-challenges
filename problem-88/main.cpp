#include <iostream>
#include <vector>

bool proizvod_5_uzastopnih(int x) {
    if (x < 120) return false; // najmanji moguci proizvod: 1*2*3*4*5 = 120
    for (int i = 1; i <= x; i++) {
        int p = i * (i + 1) * (i + 2) * (i + 3) * (i + 4);
        if (p == x) return true;
        if (p > x) break;
    }
    return false;
}

std::vector<bool> f(const std::vector<int> &v) {
    std::vector<bool> res;
    for (int e: v) res.push_back(proizvod_5_uzastopnih(e));
    return res;
}

int main() {
    std::vector<int> v{720, 110}; // true false
    auto res = f(v);
    for (int i = 0; i < res.size(); i++) std::cout << std::boolalpha << res.at(i) << " ";
    return 0;
}