// TP 2023/2024: Zadaća 4, Zadatak 2
#include <cmath>
#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

enum Pol { Musko, Zensko };

class GradjaninBiH {
public:

    explicit GradjaninBiH(std::string ime_i_prezime, long long int jmbg);
    explicit GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja,
                          int mjesec_rodjenja, int godina_rodjenja,
                          int sifra_regije, Pol p);
    ~GradjaninBiH();
    GradjaninBiH(const GradjaninBiH &g) = delete; // zabrana kopiranja
    GradjaninBiH &operator=(const GradjaninBiH &g) = delete; // zabrana dodjele
    std::string DajImeIPrezime() const { return ime_i_prezime; };
    long long int DajJMBG() const { return jmbg; }; // TODO: AT 11 ne valja, vraca jmbg bez prve nule ako ima 12 cifara
    int DajDanRodjenja() const;
    int DajMjesecRodjenja() const { return DajDioJMBG(2, 2); };
    int DajGodinuRodjenja() const;
    int DajSifruRegije() const { return DajDioJMBG(7, 2); };
    Pol DajPol() const { return (DajDioJMBG(9, 3) < 500) ? Musko : Zensko; };
    void PromijeniImeIPrezime(std::string novo_ime_i_prezime) {
        if(novo_ime_i_prezime == "")
            throw std::logic_error("Ime ne moze biti prazno!");
        ime_i_prezime = novo_ime_i_prezime;
    };

private:
    std::string ime_i_prezime;
    long long int jmbg;
    Pol pol;
    GradjaninBiH *prethodni;
    static GradjaninBiH *zadnji;
    bool ValidirajJMBG(long long int jmbg);
    int IzracunajKontrolnuCifru(const int cifre[]);
    bool PostojiLiIstiJMBG(long long int jmbg);
    void ProvjeriDatum(int dan, int mjesec, int godina);
    int DajDioJMBG(int pocetak, int duzina) const;
    static void PretvoriJMBGUNiz(long long int jmbg, int cifre[]);
    static bool DaLiJePrestupna(int godina);
};

// static attr
GradjaninBiH *GradjaninBiH::zadnji = nullptr;

int GradjaninBiH::DajGodinuRodjenja() const {
    long long int temp_jmbg = jmbg;
    int c[13];

    for (int i = 12; i >= 0; --i) {
        c[i] = temp_jmbg % 10;
        temp_jmbg /= 10;
    }

    int g = c[4] * 100 + c[5] * 10 + c[6];

    if (g > 900) {
        std::string godina_str = std::to_string(g);
        godina_str.insert(0, "1");
        g = std::stoi(godina_str);
    } else {
        std::string godina_str = std::to_string(g);
        godina_str.insert(0, "200");
        g = std::stoi(godina_str);
    }

    return g;
}

void GradjaninBiH::PretvoriJMBGUNiz(long long int jmbg, int cifre[]) {
    for (int i = 12; i >= 0; --i) {
        cifre[i] = jmbg % 10;
        jmbg /= 10;
    }
}

bool GradjaninBiH::DaLiJePrestupna(int godina) {
    return (godina % 4 == 0 && godina % 100 != 0) || (godina % 400 == 0);
}

void GradjaninBiH::ProvjeriDatum(int dan, int mjesec, int godina) {

    if (mjesec < 1 || mjesec > 12)
        throw std::logic_error("JMBG nije validan");

    int dani_u_mjesecu[]{31, (DaLiJePrestupna(godina) ? 29 : 28),
                         31, 30,
                         31, 30,
                         31, 31,
                         30, 31,
                         30, 31};

    if (dan < 1 || dan > dani_u_mjesecu[mjesec - 1])
        throw std::logic_error("JMBG nije validan");
}

int GradjaninBiH::IzracunajKontrolnuCifru(const int cifre[]) {
    int suma = 0;
    suma += 7 * (cifre[0] + cifre[6]);
    suma += 6 * (cifre[1] + cifre[7]);
    suma += 5 * (cifre[2] + cifre[8]);
    suma += 4 * (cifre[3] + cifre[9]);
    suma += 3 * (cifre[4] + cifre[10]);
    suma += 2 * (cifre[5] + cifre[11]);

    int ostatak = suma % 11;
    int kc = 11 - ostatak;
    if (kc == 11)
        kc = 0;
    return kc;
}

bool GradjaninBiH::ValidirajJMBG(long long int jmbg) {
    int cifre[13];
    PretvoriJMBGUNiz(jmbg, cifre);

    int dan = cifre[0] * 10 + cifre[1];
    int mjesec = cifre[2] * 10 + cifre[3];
    int godina = cifre[4] * 100 + cifre[5] * 10 + cifre[6];

    godina += (godina < 21) ? 2000 : 1900;

    try {
        ProvjeriDatum(dan, mjesec, godina);
    } catch (const std::logic_error &) {
        return false;
    }

    int kontrolna_c = IzracunajKontrolnuCifru(cifre);
    if (kontrolna_c == 10 || kontrolna_c != cifre[12])
        return false;
    return true;
}

// implementacija prvog konstruktora koji prima i jmbg
GradjaninBiH::GradjaninBiH(std::string i_i_p, long long int jmbg) {
    if (i_i_p.empty())
        throw std::logic_error("Ime ne moze biti prazno!");
    if (!ValidirajJMBG(jmbg))
        throw std::logic_error("JMBG nije validan");
    if (PostojiLiIstiJMBG(jmbg))
        throw std::logic_error("Vec postoji gradjanin sa istim JMBG");


    this->ime_i_prezime = i_i_p;
    this->jmbg = jmbg;

    prethodni = zadnji;
    zadnji = this;
}

GradjaninBiH::GradjaninBiH(std::string ime_i_prezime, int dan_rodjenja,
                           int mjesec_rodjenja, int godina_rodjenja,
                           int sifra_regije, Pol p) {
    ProvjeriDatum(dan_rodjenja, mjesec_rodjenja, godina_rodjenja);
    if (sifra_regije < 0 || sifra_regije > 99)
        throw std::logic_error("Neispravni podaci");

    if (ime_i_prezime.empty())
        throw std::logic_error("Ime ne moze biti prazno!");

    int kod_osobe_pocetak = (p == Musko) ? 0 : 500;
    int kod_osobe_kraj = (p == Musko) ? 499 : 999;

    int cifre[13];
    cifre[0] = dan_rodjenja / 10;
    cifre[1] = dan_rodjenja % 10;
    cifre[2] = mjesec_rodjenja / 10;
    cifre[3] = mjesec_rodjenja % 10;
    cifre[4] = (godina_rodjenja / 100) % 10;
    cifre[5] = (godina_rodjenja / 10) % 10;
    cifre[6] = godina_rodjenja % 10;
    cifre[7] = sifra_regije / 10;
    cifre[8] = sifra_regije % 10;

    bool nadjen_jmbg = false;
    for (int kod = kod_osobe_pocetak; kod <= kod_osobe_kraj; ++kod) {
        cifre[9] = kod / 100;
        cifre[10] = (kod / 10) % 10;
        cifre[11] = kod % 10;

        int kontrolna_cifra = IzracunajKontrolnuCifru(cifre);
        if (kontrolna_cifra == 10)
            continue;
        cifre[12] = kontrolna_cifra;

        long long int novi_jmbg = 0;
        for (int i = 0; i < 13; ++i) {
            novi_jmbg = novi_jmbg * 10 + cifre[i];
        }

        if (!ValidirajJMBG(novi_jmbg))
            continue;

        bool postoji_isti_jmbg = false;
        for (GradjaninBiH *p = zadnji; p != nullptr; p = p->prethodni) {
            if (p->DajJMBG() == novi_jmbg) {
                postoji_isti_jmbg = true;
                break;
            }
        }

        if (!postoji_isti_jmbg) {
            this->ime_i_prezime = ime_i_prezime;
            this->jmbg = novi_jmbg;
            this->pol = p;

            prethodni = zadnji;
            zadnji = this;
            nadjen_jmbg = true;
            break;
        }
    }
    if (!nadjen_jmbg)
        throw std::logic_error("Neispravni podaci");
}

GradjaninBiH::~GradjaninBiH() {
    if (this == zadnji) {
        zadnji = prethodni;
    } else {
        for (GradjaninBiH *p = zadnji; p != nullptr; p = p->prethodni) {
            if (p->prethodni == this) {
                p->prethodni = prethodni;
                break;
            }
        }
    }
}

int GradjaninBiH::DajDioJMBG(int pocetak, int duzina) const {
    long long int temp_jmbg = jmbg;
    int faktor = 1;
    for (int i = 0; i < (13 - pocetak - duzina); ++i) {
        faktor *= 10;
    }
    temp_jmbg /= faktor;
    int dio_jmbg = temp_jmbg % (int)pow(10, duzina);
    return dio_jmbg;
}

bool GradjaninBiH::PostojiLiIstiJMBG(long long int jmbg) {
    for (GradjaninBiH *p = zadnji; p != nullptr; p = p->prethodni)
        if (p->jmbg == jmbg)
            return true;
    return false;
}

int GradjaninBiH::DajDanRodjenja() const {
    std::string jmbg_str = std::to_string(jmbg);
    int dan = std::stoi(jmbg_str.substr(0, 2));

    if (dan > 31) {
        std::string jmbg_str = std::to_string(jmbg);
        return std::stoi(jmbg_str.substr(0, 1));
    }
    return dan;
}

int main() {

    // AT 13 - passing
//    try {
//        GradjaninBiH osoba("Milica Milic", 5, 12, 2001, 28, Pol::Zensko);
//        std::cout << "Ispravno kreiran: " << osoba.DajImeIPrezime() << " JMBG: " << osoba.DajJMBG() << std::endl;
//    } catch (const std::logic_error& e) {
//        std::cout << "Greska: " << e.what() << std::endl;
//    }

    // AT 12 - passing
//    try {
//        GradjaninBiH neispravanJMBG("Mujo Mujic", 1234567890123);
//    } catch (const std::logic_error& e) {
//        std::cout << "Greska: " << e.what() << std::endl;
//    }
//    try {
//        GradjaninBiH neispravanJMBG("", 1234567890123);
//    } catch (const std::logic_error& e) {
//        std::cout << "Greska: " << e.what() << std::endl;
//    }
//    try {
//        GradjaninBiH praznoIme("", 707995130005);
//    } catch (const std::logic_error& e) {
//        std::cout << "Greska: " << e.what() << std::endl;
//    }
//    try {
//        GradjaninBiH ispravan("Hana Hanic", 707995135015);
//        std::cout << "Ispravno kreiran: " << ispravan.DajImeIPrezime() << " JMBG: " << ispravan.DajJMBG() << std::endl;
//    } catch (const std::exception& e) {
//        std::cout << "Nesto nije u redu: " << e.what() << std::endl;
//    }

    // AT 8 - passing
//    if (!std::is_copy_constructible<GradjaninBiH>::value)
//        std::cout << "Kopiranje GradjaninBiH zabranjeno!" << std::endl;
//    else std::cout << "Kopiranje GradjaninBiH treba biti zabranjeno!" << std::endl;

    // AT 7 - passing
//    if (!std::is_copy_assignable<GradjaninBiH>::value)
//        std::cout << "Dodjeljivanje GradjaninBiH zabranjeno!" << std::endl;
//    else std::cout << "Dodjeljivanje GradjaninBiH treba biti zabranjeno!" << std::endl;

    // AT 9 - passing
//    try {
//        GradjaninBiH osoba("Mujo Mujic", 1305956174235);
//        std::cout << "Ime gradjanina: " << osoba.DajImeIPrezime() << std::endl;
//
//        osoba.PromijeniImeIPrezime("Mujo Suljic");
//        std::cout << "Novo ime nakon prve promjene: " << osoba.DajImeIPrezime() << std::endl;
//
//        osoba.PromijeniImeIPrezime("Suljo Suljic");
//        std::cout << "Novo ime nakon druge promjene: " << osoba.DajImeIPrezime() << std::endl;
//
//        osoba.PromijeniImeIPrezime("");
//        std::cout << "Novo ime nakon treće promjene: " << osoba.DajImeIPrezime() << std::endl;
//
//    } catch (const std::exception& e) {
//        std::cout << "Izuzetak: " << e.what() << std::endl;
//    }
    try {
        int broj_gradjana;
        std::cout << "Unesite broj gradjana: ";
        std::cin >> broj_gradjana;
        std::cout << std::endl;

        GradjaninBiH **g = new GradjaninBiH *[broj_gradjana] {};
        int broj_kreiranih = 0;

        for (int i = 1; i <= broj_gradjana; i++) {
            std::cout << "Unesite podatke za " << i << ". gradjanina:\n";
            std::cout << "Ime i prezime: ";
            std::string ime_i_prezime;
            std::cin.ignore();
            std::getline(std::cin, ime_i_prezime);

            int dan, mjesec, godina, sifra_regije, pol;
            std::cout << "Datum rodjenja: ";
            std::cin >> dan >> mjesec >> godina;
            std::cout << "Sifra regije: ";
            std::cin >> sifra_regije;
            std::cout << "Pol ( 1-Musko, 2-Zensko ): ";
            std::cin >> pol;
            std::cout << std::endl;

            try {
                auto pol_enum = (pol == 1) ? Pol::Musko : Pol::Zensko;
                g[broj_kreiranih++] = new GradjaninBiH(ime_i_prezime, dan, mjesec,
                                                       godina, sifra_regije, pol_enum);
            } catch (const std::logic_error &e) {
                std::cout << "Neispravni podaci. Molimo ponovite unos.\n";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                i--;
            }
        }

        // sortiranje po starosti
        for (int i = 0; i < broj_kreiranih - 1; i++) {
            for (int j = i + 1; j < broj_kreiranih; j++) {
                bool zamijeniti = false;
                if (g[i]->DajGodinuRodjenja() > g[j]->DajGodinuRodjenja())
                    zamijeniti = true;
                else if (g[i]->DajGodinuRodjenja() == g[j]->DajGodinuRodjenja()) {
                    if (g[i]->DajMjesecRodjenja() > g[j]->DajMjesecRodjenja())
                        zamijeniti = true;
                    else if (g[i]->DajMjesecRodjenja() == g[j]->DajMjesecRodjenja()) {
                        if (g[i]->DajDanRodjenja() > g[j]->DajDanRodjenja())
                            zamijeniti = true;
                    }
                }
                if (zamijeniti) {
                    GradjaninBiH *temp = g[i];
                    g[i] = g[j];
                    g[j] = temp;
                }
            }
        }

        std::cout << "Gradjani sortirani po starosti:\n";
        for (int i = 0; i < broj_kreiranih; i++)
            std::cout << g[i]->DajImeIPrezime() << " " << g[i]->DajDanRodjenja()
                      << "." << g[i]->DajMjesecRodjenja() << "."
                      << g[i]->DajGodinuRodjenja() << " JMBG: " << g[i]->DajJMBG()
                      << std::endl;

        for (int i = 0; i < broj_kreiranih; i++)
            delete g[i];
        delete[] g;
    } catch (const std::exception &e) {
        std::cout << "Greska: " << e.what() << std::endl;
    }
    return 0;
}
