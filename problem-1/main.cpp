#include <iostream>
#include <vector>

bool TestPerioda(const std::vector<double> &v, int p);
int OdrediOsnovniPeriod(const std::vector<double> &v);

int main() {
    std::cout << "Unesite slijed brojeva (0 za kraj): ";
    std::vector<double> v;
    int x;
    while (std::cin >> x && x != 0)
        v.push_back(x);
    int result = OdrediOsnovniPeriod(v);
    if(result != -1)
        std::cout << "Slijed je periodican sa osnovnim periodom: " << result << "." << std::endl;
    else
        std::cout << "Slijed nije periodican!" << std::endl;
    return 0;
}


bool TestPerioda(const std::vector<double> &v, int p) {
    if (p >= v.size() || p < 1) return false;
    for (int i = 0; i < v.size() - p; i++) { // v.size() - p cheeky
        if (v.at(i) != v.at(i + p))
            return false;
    }
    return true;
}

int OdrediOsnovniPeriod(const std::vector<double> &v) {
    for (int p = 1; p < v.size(); p++) {
        if (TestPerioda(v, p))
            return p;
    }
    return -1;
}