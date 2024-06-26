#include <iostream>
#include <iomanip>
#include <cstring>
#include <stdexcept>

class Tim {
private:
    char ime_tima[21];
    int broj_odigranih;
    int broj_pobjeda;
    int broj_nerijesenih;
    int broj_poraza;
    int broj_datih;
    int broj_primljenih;
    int broj_poena;
public:
    Tim(const char ime[]);
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *DajImeTima() const { return ime_tima; };
    int DajBrojPoena() const { return broj_poena; };
    int DajGolRazliku() const { return broj_datih - broj_primljenih; };
    void IspisiPodatke() const;
};

Tim::Tim(const char ime[]) : broj_odigranih(0), broj_pobjeda(0), broj_nerijesenih(0), broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0) {
    if (strlen(ime) > 20) throw std::range_error("Predugacko ime tima");
    std::strcpy(ime_tima, ime);
}

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    if(broj_datih < 0 || broj_primljenih < 0) throw std::range_error("Neispravan broj golova");
    broj_odigranih++;
    this->broj_datih += broj_datih;
    this->broj_primljenih += broj_primljenih;
    if(broj_datih > broj_primljenih) {
        broj_pobjeda++;
        broj_poena += 3;
    } else if(broj_datih == broj_primljenih) {
        broj_nerijesenih++;
        broj_poena++;
    } else {
        broj_poraza++;
    }
}

void Tim::IspisiPodatke() const {
    std::cout <<
    std::left << std::setw(20) << ime_tima <<
    std::right << std::setw(4) << broj_odigranih <<
    std::setw(4) << broj_pobjeda <<
    std::setw(4) << broj_nerijesenih <<
    std::setw(4) << broj_poraza <<
    std::setw(4) << broj_datih <<
    std::setw(4) << broj_primljenih <<
    std::setw(4) << broj_poena <<
    std::endl;
}

int main() {
    Tim t1("Al-Nassr FC"), t2("Inter Miami");
    t1.ObradiUtakmicu(6, 0);
    t2.ObradiUtakmicu(0, 6);
    t1.IspisiPodatke();
    t2.IspisiPodatke();
    return 0;
}
