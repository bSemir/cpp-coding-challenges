#include <iostream>
#include <functional>
#include <fstream>
#include <stdexcept>
#include <string>

template<typename T>
void SifrirajBinarnuDatoteku(const std::string &ime_datoteke, std::function<T(T)> funkcija_sifriranja) {
    std::fstream tok(ime_datoteke, std::ios::in | std::ios::out | std::ios::binary);
    if (!tok) throw std::logic_error("Datoteka ne postoji");

    T x;
    while (tok.read(reinterpret_cast<char *>(&x), sizeof x)) {
        x = funkcija_sifriranja(x);
        tok.seekp(int(tok.tellg()) - sizeof x); // pomjeramo kurzor na tekucu poziciju (prepisujemo preko trenutnog)
        tok.write(reinterpret_cast<char *>(&x), sizeof x);
        tok.seekg(0, std::ios::cur); // pozivamo seekg zbog prelaska na citanje
    }
    if (!tok.eof())
        throw std::logic_error("Neuspjesno citanje ili pisanje!");
}

void KreirajBinarnuDatoteku(const std::string &ime_datoteke, const std::string &sadrzaj) {
    std::fstream tok(ime_datoteke, std::ios::out | std::ios::binary);
    if (!tok) throw std::logic_error("Neuspjesno kreiranje datoteke");

    tok.write(reinterpret_cast<const char *>(sadrzaj.c_str()), sadrzaj.size());
    std::cout << "U datoteku upisano:👇\n" << sadrzaj << std::endl;
}

int main() {
    try {
        KreirajBinarnuDatoteku("test.bin", "Cristiano Ronaldo > Messi");
        SifrirajBinarnuDatoteku<int>("test.bin", [](int x) {
            return x + 2;
        });
    } catch (std::exception &e) {
        std::cout << "Exception ->: " << e.what() << std::endl;
    }
    return 0;
}
