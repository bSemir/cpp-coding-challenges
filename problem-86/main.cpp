#include <iostream>
#include <string>

void dodaj_n_razmaka(std::string &s, int n) {
    for (int i = 0; i < s.size(); i += n + 1) {
        for (int j = 0; j < n; j++)
            s.insert(s.begin() + i + j + 1, ' ');
    }
}

int main() {
    std::string s = "lopta";
    std::cout << "Before: " << s << std::endl;
    dodaj_n_razmaka(s, 2);
    std::cout << "After: " << s << std::endl;
    return 0;
}
