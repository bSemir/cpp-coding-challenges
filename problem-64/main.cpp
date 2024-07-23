#include <iostream>
#include <string>
#include <array>

std::array<int, 26> Prebrojavanje(const std::string &s) {
    std::array<int, 26> broj_slova{}; // inicijalizacija na 0
    for (char c: s) {
        if (c >= 'a' && c <= 'z') { // mala slova
            broj_slova[c - 'a']++; // 'a' - 'a' = 0, 'b' - 'a' = 1, ...
        } else if (c >= 'A' && c <= 'Z') { // velika slova
            broj_slova[c - 'A']++; // 'A' - 'A' = 0, 'B' - 'A' = 1, ...
        }
    }
    return broj_slova;
}

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    auto broj_slova = Prebrojavanje(s);

    for (int i = 0; i < broj_slova.size() / 2; i++)
        std::cout << (char) ('a' + i) << ": " << broj_slova[i] << " ";

    std::cout << std::endl;

    for (int i = broj_slova.size() / 2; i < broj_slova.size(); i++)
        std::cout << (char) ('a' + i) << ": " << broj_slova[i] << " ";

    return 0;
}