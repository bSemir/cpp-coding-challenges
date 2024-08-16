#include <iostream>
#include <list>
#include <cmath>

bool areEqual(const double &x, const double &y) {
    const double EPSILON = 1e-9;
    return std::fabs(x - y) < EPSILON;
}

int PeriodListe(const std::list<double> &l) {
    int n = l.size();
    for (int T = 1; T <= n / 2; T++) {
        auto it1 = l.begin();
        auto it2 = std::next(l.begin(), T);
        bool periodic = true;

        for (int i = 0; i + T < n; i++) {
            if (!areEqual(*it1, *it2)) {
                periodic = false;
                break;
            }
            ++it1;
            ++it2;
        }
        if (periodic) return T;
    }
    return 0;
}

int main() {
    std::list<double> l{5, 9, 7, 2, 5, 9, 7, 2, 5, 9, 7};
    int period = PeriodListe(l);
    if (period == 0)
        std::cout << "0 - slijed brojeva nije periodican!\n";
    else
        std::cout << "Slijed brojeva je periodican s periodom " << period;
    return 0;
}