#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

void izvrni_datoteku(const std::string &ime_datoteke) {
    std::fstream tok(ime_datoteke, std::ios::binary | std::ios::in | std::ios::out);
    if (!tok) throw std::logic_error("Datoteka ne postoji");

    tok.seekg(0, std::ios::end);
    int velicina = sizeof(double);
    int broj_elemenata = tok.tellg() / velicina;

    // izvrni sadrzaj binarne datoteke, kao "u ogledalu"
    for (int i = 0; i < broj_elemenata / 2; i++) {
        tok.seekg(i * velicina, std::ios::beg); //
        double prvi;
        tok.read(reinterpret_cast<char *>(&prvi), velicina);

        tok.seekg((broj_elemenata - i - 1) * velicina, std::ios::beg);
        double drugi;
        tok.read(reinterpret_cast<char *>(&drugi), velicina);

        tok.seekp(i * velicina, std::ios::beg);
        tok.write(reinterpret_cast<char *>(&drugi), velicina);

        tok.seekp((broj_elemenata - i - 1) * velicina, std::ios::beg);
        tok.write(reinterpret_cast<char *>(&prvi), velicina);

        if (!tok) throw std::logic_error("Problemi prilikom upisa u datoteku");
    }
}

int main() {
    std::fstream tok("brojevi.bin", std::ios::binary | std::ios::out);
    double kvadrat;
    for (int i = 1; i <= 7; i++) {
        kvadrat = i * i;
        tok.write(reinterpret_cast<char *>(&kvadrat), sizeof(double));
    }
    tok.close();
    izvrni_datoteku("brojevi.bin");
    tok.open("brojevi.bin", std::ios::binary | std::ios::in);

    for (int i = 1; i <= 7; i++) {
        tok.read(reinterpret_cast<char *>(&kvadrat), sizeof(double));
        std::cout << kvadrat << std::endl;
    }
    return 0;
}
