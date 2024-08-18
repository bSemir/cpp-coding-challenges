#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>

bool DaLiSadrziSlova(const std::string &s) {
    return std::count_if(s.begin(), s.end(), [](char c) { return std::isalpha(c); }) > 3;
}

std::string IzbaciSuvisneRazmake(std::string &s) {
    if (s.length() == 0 || s.length() < 4)
        throw std::domain_error("Neispravan string!");
    if (!DaLiSadrziSlova(s)) throw "Neispravna recenica!";
    std::string result;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) != ' ') {
            std::string word;
            while (s.at(i) != ' ') word.push_back(s[i++]);
            result = result + word + ' ';
        }
    }
    return result;
}

// TODO: remove spaces at the end if found, implement better algorithm to check if sentence is valid

int main() {
    try {
        std::cout << "Unesite recenicu: "; //   "   Ovo    je primjer.    "
        std::string sentence;
        std::getline(std::cin, sentence);
        std::string result = IzbaciSuvisneRazmake(sentence);
        std::cout << "👉" << result << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}