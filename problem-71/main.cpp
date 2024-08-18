#include <iostream>
#include <string>

std::string IzbaciSuvisneRazmake(std::string &s) {
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

// TODO: remove spaces at the end if found, try-catch..

int main() {
    std::cout << "Unesite recenicu: "; //   "   Ovo    je primjer.    "
    std::string sentence;
    std::getline(std::cin, sentence);
    std::string result = IzbaciSuvisneRazmake(sentence);
    std::cout << "👉" << result << std::endl;
    return 0;
}