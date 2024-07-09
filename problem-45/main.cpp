#include <iostream>
#include <string>
#include <cctype>

std::string pretvori_u_satrovacki(const std::string &recenica) {
    std::string s;
    for (char c: recenica) {
        char malo_slovo = std::tolower(c); // pretvaramo svako slovo u malo
        s += c; // dodajemo charove iz recenice
        if (malo_slovo == 'a' || malo_slovo == 'e' || malo_slovo == 'i' || malo_slovo == 'o' || malo_slovo == 'u')
            s = s + 'p' + malo_slovo;
    }
    return s;
}

int main() {
    std::cout << "Unesite recenicu: ";
    std::string recenica;
    std::getline(std::cin, recenica);
    std::cout << "Satrovacki: " << pretvori_u_satrovacki(recenica) << std::endl;
    return 0;
}