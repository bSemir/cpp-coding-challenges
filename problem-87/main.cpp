#include <iostream>
#include <string>

void ROT13(std::string &s) {
    for (char &c: s) {
        if ((c >= 'A' && c <= 'M') || (c >= 'a' && c <= 'm'))
            c += 13; // c = char(c + 13)
        else if ((c >= 'N' && c <= 'Z') || (c >= 'n' && c <= 'z'))
            c -= 13;
    }
}

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    ROT13(s);
    std::cout << "String transformisan po ROT13 sistemu glasi: " << s << std::endl;
    // ABC-D -> NOP-Q ✅
    // NOP-Q -> ABC-D ✅
    return 0;
}
