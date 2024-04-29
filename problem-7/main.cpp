#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

std::vector<std::string> IzdvojiSimetricneRijeci(const std::string &s);
bool jeLiSimetricna(std::string rijec);

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    std::vector<std::string> v = IzdvojiSimetricneRijeci(s);
    std::cout << "Simetricne rijeci: ";
    // for(const auto &el : v) std::cout << el << ", ";
    for(int i = 0; i < v.size(); i++) {
        if (i == v.size() - 1) std::cout << v.at(i);
        else std::cout << v.at(i) << ", ";
    }
    return 0;
}

std::vector<std::string> IzdvojiSimetricneRijeci(const std::string &s) {
    std::vector<std::string> v;
    for(int i = 0; i < s.size(); i++) {
        if(std::isalpha(s[i]) && (i == 0 || !std::isalpha(s[i - 1]))) {
            std::string word;
            while(i < s.length() && std::isalpha(s[i])) word += s[i++];
            std::cout << "curr word: " << word << '\n';
            if(word.length() >= 2 && jeLiSimetricna(word))
                v.push_back(word);
        }
    }
    return v;
}

bool jeLiSimetricna(std::string rijec) {
    // we intentionally don't use reference here
    std::transform(rijec.begin(), rijec.end(), rijec.begin(), ::tolower);
    return std::equal(rijec.begin(), rijec.end(), rijec.rbegin());
}
