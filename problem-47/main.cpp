#include <iostream>
#include <vector>
#include <string>

bool jeLiSimetrican(const std::string &str) {
    if (str.length() <= 1) return false;
    int i = 0, j = str.length() - 1;
    while (i < j) {
        if (str.at(i) != str.at(j)) return false;
        i++;
        j--;
    }
    return true;
}

std::vector<std::string> dajPodstringove(const std::string &s) {
    std::vector<std::string> v;
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) != ' ' && (i == 0 || s.at(i - 1) == ' ')) {
            std::string rijec;
            while (s[i] != ' ' && i < s.length()) rijec.push_back(s[i++]);
            if (jeLiSimetrican(rijec)) v.push_back(rijec);
        }
    }
    return v;
}

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    std::cout << "Simetricni podstringovi: " << std::endl;
    auto result = dajPodstringove(s);
    for (const auto &x: result) std::cout << x << std::endl;
    return 0;
}