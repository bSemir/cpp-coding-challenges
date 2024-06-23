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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
