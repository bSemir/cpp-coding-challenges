#include <iostream>
#include <string>
#include <stdexcept>

std::string f(std::string &s, char &znak) {
    std::string result;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) != ' ' && (i == 0 || s.at(i - 1) == ' ')) {
            std::string word;
            while (i < s.size() && s.at(i) != ' ') {
                word.push_back(s[i++]);
            }
            result = result + word + znak;
        }
    }
    if (!result.empty() && result[result.size() - 1] == znak)
        result.pop_back();
    return result;
}

int main() {
    std::string s = "   Danas   je ispit  iz TP-a";
    char znak = ',';
    std::string r = f(s, znak);
    std::cout << r << std::endl;
    return 0;
}