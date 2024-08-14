#include <iostream>
#include <deque>

bool DaLiSuJednaki(const std::deque<int> &d1, const std::deque<int> &d2) {
    if (d1.size() != d2.size()) return false;
    for (int i = 0; i < d1.size(); i++)
        if (d1.at(i) != d2.at(i)) return false;

    return true;
}

bool DaLiJeCirkulantna(const std::deque<std::deque<int>> &d) {
    // ima li oblik kvadratne matrice
    for (int i = 0; i < d.size(); i++) {
        if (d[i].size() != d.size()) return false;
    }

    for (int i = 1; i < d.size(); i++) {
        std::deque<int> previous_row(d[i - 1].size());
        std::copy(d[i - 1].begin(), d[i - 1].end(), previous_row.begin());

        // pomjeranje prethodnog reda udesno
        std::deque<int> row;
        row.push_back(previous_row[previous_row.size() - 1]); // zadnji element prethodnog reda
        for (int j = 0; j < previous_row.size() - 1; j++) // ostatak prethodnog reda
            row.push_back(previous_row[j]);

        // is current red jednak ciklicki pomjerenom prethodnom redu
        // if (!DaLiSuJednaki(row, d[i])) return false;
        if (row != d[i]) return false;
    }
    return true;
}

int main() {
    std::deque<std::deque<int>> d{{1, 2, 3, 4},
                                  {4, 1, 2, 3},
                                  {3, 4, 1, 2},
                                  {2, 3, 4, 1}};
    std::cout << std::boolalpha << DaLiJeCirkulantna(d) << std::endl;
    return 0;
}