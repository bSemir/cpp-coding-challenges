#include <iostream>
#include <string>

void ROT13(std::string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (s.at(i) >= 'A' && s.at(i) <= 'M' || ((s.at(i) >= 'a' && s.at(i) <= 'm')))
            s.at(i) = char(s.at(i) + 13);
        else if (s.at(i) >= 'N' && s.at(i) <= 'Z' || ((s.at(i) >= 'a' && s.at(i) <= 'm')))
            s.at(i) = char(s.at(i) - 13);
    }
}

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    ROT13(s);
    std::cout << "String transformisan po ROT13 sistemu glasi: " << s << std::endl;
    // ABC -> NOP ✅
    return 0;
}
