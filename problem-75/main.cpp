#include <iostream>
#include <string>

template<typename T1, typename T2>
T1 KopirajBezDuplikata(T1 pocetak, T1 iza_kraja, T2 odrediste) {
    for (auto p = pocetak; p != iza_kraja; p++) {
        bool unique = true;
        // da li je vidjen ranije
        for (auto q = pocetak; q != p; q++) {
            if (*q == *p) {
                unique = false;
                break;
            }
        }
        if (unique)
            *odrediste++ = *p;
    }
    return odrediste;
}

int main() {
    std::cout << "Unesite string: ";
    std::string s;
    std::getline(std::cin, s);
    std::string result(s.size(), ' '); // dest str must not be empty
    auto kraj_novog = KopirajBezDuplikata(s.begin(), s.end(), result.begin());
    result.resize(kraj_novog - result.begin());
    std::cout << "String bez duplikata: " << result << std::endl;
    return 0;
}
