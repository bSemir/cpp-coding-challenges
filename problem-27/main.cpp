#include <algorithm>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

class Datum {
private:
    int dan, mjesec, godina;

public:
    Datum(int dan, int mjesec, int godina) { Postavi(dan, mjesec, godina); }

    Datum &Postavi(int dan, int mjesec, int godina) {
        IsDatumValid(dan, mjesec, godina);
        Datum::dan = dan;
        Datum::mjesec = mjesec;
        Datum::godina = godina;
        return *this;
    }

    std::tuple<int, int, int> Ocitaj() const {
        return std::make_tuple(dan, mjesec, godina);
    }

    void Ispisi() const { std::cout << dan << "/" << mjesec << "/" << godina; }

    static bool IsPrestupna(int godina) {
        return (godina % 4 == 0 && godina % 100 != 0) || godina % 400 == 0;
    }

    void IsDatumValid(int dan, int mjesec, int godina) const;
};

void Datum::IsDatumValid(int dan, int mjesec, int godina) const {
    if (mjesec < 1 || mjesec > 12)
        throw std::domain_error("Neispravan datum");

    int dani_u_mjesecu[]{
            31, (IsPrestupna(godina) ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30,
            31};

    if (dan < 1 || dan > dani_u_mjesecu[mjesec - 1])
        throw std::domain_error("Neispravan datum");
}

class Vrijeme {
    int sati, minute;

public:
    Vrijeme(int sati, int minute) { Postavi(sati, minute); }
    Vrijeme &Postavi(int sati, int minute) {
        if (sati < 0 || sati > 23 || minute < 0 || minute > 59)
            throw std::domain_error("Neispravno vrijeme");
        Vrijeme::sati = sati;
        Vrijeme::minute = minute;
        return *this;
    }
    std::pair<int, int> Ocitaj() const { return std::make_pair(sati, minute); }
    void Ispisi() const {
        // std::cout << std::setw(2) << std::setfill(' ') << sati << ":"
        //           << std::setw(2) << std::setfill(' ') << minute;
        if (sati < 10)
            std::cout << std::setw(2) << std::setfill(' ') << "0";
        std::cout << sati << ":";
        if (minute < 10)
            std::cout << "0";
        std::cout << minute;
    }
};

class Pregled {
    std::string imePacijenta;
    Datum danPregleda;
    Vrijeme vrijemePregleda;

public:
    Pregled(const std::string &ime_pacijenta, const Datum &dan_pregleda,
            const Vrijeme &vrijeme_pregleda)
            : imePacijenta(ime_pacijenta), danPregleda(dan_pregleda),
              vrijemePregleda(vrijeme_pregleda) {}

    Pregled(const std::string &ime_pacijenta, int dan, int mjesec, int godina,
            int sati, int minute)
            : imePacijenta(ime_pacijenta), danPregleda(dan, mjesec, godina),
              vrijemePregleda(sati, minute) {}

    Pregled &PromijeniPacijenta(const std::string &novo_ime) {
        if (novo_ime.empty())
            throw std::domain_error("Ime ne moze biti prazno!");
        imePacijenta = novo_ime;
        return *this;
    }

    Pregled &PromijeniDatum(const Datum &novi_datum) {
        danPregleda = novi_datum;
        return *this;
    }

    Pregled &PromijeniVrijeme(const Vrijeme &novo_vrijeme) {
        vrijemePregleda = novo_vrijeme;
        return *this;
    }

    void PomjeriDanUnaprijed();

    void PomjeriDanUnazad();

    std::string DajImePacijenta() const { return imePacijenta; }

    Datum DajDatumPregleda() const { return danPregleda; }

    Vrijeme DajVrijemePregleda() const { return vrijemePregleda; }

    static bool DolaziPrije(const Pregled &p1, const Pregled &p2) {
        return p1.danPregleda.Ocitaj() < p2.danPregleda.Ocitaj();
    }

    void Ispisi() const {
        std::cout << std::left << std::setw(30) << imePacijenta;
        danPregleda.Ispisi();
        std::cout << " ";
        vrijemePregleda.Ispisi();
        std::cout << "\n";
    }
};

void Pregled::PomjeriDanUnaprijed() {
    int dan, mjesec, godina;
    std::tie(dan, mjesec, godina) = danPregleda.Ocitaj();
    dan++;
    if (dan > 31) {
        dan = 1;
        mjesec++;
        if (mjesec > 12) {
            mjesec = 1;
            godina++;
        }
    }
    danPregleda.Postavi(dan, mjesec, godina);
}

void Pregled::PomjeriDanUnazad() {
    int dan, mjesec, godina;
    std::tie(dan, mjesec, godina) = danPregleda.Ocitaj();
    dan--;
    if (dan < 1) {
        mjesec--;
        if (mjesec < 1) {
            godina--;
            mjesec = 12;
        }
        dan = Datum::IsPrestupna(godina) ? 29 : 28;
    }
    danPregleda.Postavi(dan, mjesec, godina);
}

class Pregledi {
private:
    Pregled **pok_na_preglede;
    int max_br_pregleda;
    int trenutni_br_pregleda;
    void Dealociraj();

public:
    Pregledi(int max_br_pregleda)
            : max_br_pregleda(max_br_pregleda), trenutni_br_pregleda(0),
              pok_na_preglede(new Pregled *[max_br_pregleda] {}) {}

    Pregledi(std::initializer_list<Pregled> lista_pregleda);
    ~Pregledi() { Dealociraj(); }
    Pregledi(const Pregledi &p);
    Pregledi(Pregledi &&p);
    Pregledi &operator=(const Pregledi &p);
    Pregledi &operator=(Pregledi &&p);
    void RegistrirajPregled(const std::string &name, const Datum &date,
                            const Vrijeme &time);
    void RegistrirajPregled(const std::string &name, int dan, int mjesec,
                            int godina, int sati, int minute);
    void RegistrirajPregled(Pregled *pregled);
    int DajBrojPregleda() const { return trenutni_br_pregleda; }
    int DajBrojPregledaNaDatum(const Datum &d) const;
    Pregled &DajNajranijiPregled();
    const Pregled &DajNajranijiPregled() const;
    void IsprazniKolekciju();
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime);
    void IspisiPregledeNaDatum(const Datum &d) const;
    void IspisiSvePreglede() const;
};

void Pregledi::Dealociraj() {
    for (int i = 0; i < trenutni_br_pregleda; i++)
        delete pok_na_preglede[i];
    delete[] pok_na_preglede;
}

Pregledi::Pregledi(std::initializer_list<Pregled> lista_pregleda) {
    try {
        max_br_pregleda = lista_pregleda.size();
        trenutni_br_pregleda = 0;
        pok_na_preglede = new Pregled *[max_br_pregleda] {}; // lopata
        for (const auto &pregled : lista_pregleda) {
            pok_na_preglede[trenutni_br_pregleda++] = new Pregled(pregled);
        }
    } catch (...) {
        Dealociraj();
        throw;
    }
}

Pregledi::Pregledi(const Pregledi &p)
        : max_br_pregleda(p.max_br_pregleda),
          trenutni_br_pregleda(p.trenutni_br_pregleda),
          pok_na_preglede(new Pregled *[p.max_br_pregleda] {}) {
    try {
        for (int i = 0; i < trenutni_br_pregleda; i++) {
            pok_na_preglede[i] = new Pregled(*p.pok_na_preglede[i]);
        }
    } catch (...) {
        Dealociraj();
        throw;
    }
}

Pregledi::Pregledi(Pregledi &&p)
        : max_br_pregleda(p.max_br_pregleda),
          trenutni_br_pregleda(p.trenutni_br_pregleda),
          pok_na_preglede(p.pok_na_preglede) {
    p.max_br_pregleda = 0;
    p.trenutni_br_pregleda = 0;
    p.pok_na_preglede = nullptr;
}

Pregledi &Pregledi::operator=(const Pregledi &p) {
    if (this == &p)
        return *this;
    try {
        Dealociraj();
        max_br_pregleda = p.max_br_pregleda;
        trenutni_br_pregleda = p.trenutni_br_pregleda;
        pok_na_preglede = new Pregled *[max_br_pregleda] {};
        for (int i = 0; i < trenutni_br_pregleda; i++)
            pok_na_preglede[i] = new Pregled(*p.pok_na_preglede[i]);
    } catch (...) {
        Dealociraj();
        throw;
    }
    return *this;
}

Pregledi &Pregledi::operator=(Pregledi &&p) {
    if (this == &p)
        return *this;
    Dealociraj();
    max_br_pregleda = p.max_br_pregleda;
    trenutni_br_pregleda = p.trenutni_br_pregleda;
    pok_na_preglede = p.pok_na_preglede;
    p.pok_na_preglede = nullptr;
    p.trenutni_br_pregleda = 0;
    p.max_br_pregleda = 0;
    return *this;
}

void Pregledi::RegistrirajPregled(const std::string &name, const Datum &date,
                                  const Vrijeme &time) {
    if (trenutni_br_pregleda >= max_br_pregleda) {
        throw std::range_error("Dostignut maksimalni broj pregleda");
    }
    pok_na_preglede[trenutni_br_pregleda++] = new Pregled(name, date, time);
}

void Pregledi::RegistrirajPregled(const std::string &name, int dan, int mjesec,
                                  int godina, int sati, int minute) {
    if (trenutni_br_pregleda >= max_br_pregleda) {
        throw std::range_error("Dostignut maksimalni broj pregleda");
    }
    pok_na_preglede[trenutni_br_pregleda++] =
            new Pregled(name, dan, mjesec, godina, sati, minute);

    //   pok_na_preglede[trenutni_br_pregleda++] =
    //       new Pregled(name, Datum(dan, mjesec, godina), Vrijeme(sati, minute));

    //   RegistrirajPregled(name, Datum(dan, mjesec, godina), Vrijeme(sati,
    //   minute));
}

void Pregledi::RegistrirajPregled(Pregled *pregled) {
    if (trenutni_br_pregleda >= max_br_pregleda)
        throw std::range_error("Dostignut maksimalni broj pregleda");
    pok_na_preglede[trenutni_br_pregleda++] = pregled;
}

int Pregledi::DajBrojPregledaNaDatum(const Datum &d) const {
    return std::count_if(
            pok_na_preglede, pok_na_preglede + trenutni_br_pregleda,
            [d](Pregled *p) { return p->DajDatumPregleda().Ocitaj() == d.Ocitaj(); });
}

Pregled &Pregledi::DajNajranijiPregled() {
    if (trenutni_br_pregleda == 0)
        throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(
            pok_na_preglede, pok_na_preglede + trenutni_br_pregleda,
            [](Pregled *p1, Pregled *p2) { return Pregled::DolaziPrije(*p1, *p2); });
}

const Pregled &Pregledi::DajNajranijiPregled() const {
    if (trenutni_br_pregleda == 0)
        throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(
            pok_na_preglede, pok_na_preglede + trenutni_br_pregleda,
            [](Pregled *p1, Pregled *p2) { return Pregled::DolaziPrije(*p1, *p2); });
}

void Pregledi::IsprazniKolekciju() {
    for (int i = 0; i < trenutni_br_pregleda; i++)
        delete pok_na_preglede[i];
    trenutni_br_pregleda = 0;
}

void Pregledi::ObrisiNajranijiPregled() {
    if (trenutni_br_pregleda == 0)
        throw std::range_error("Prazna kolekcija");

    auto it = std::min_element(
            pok_na_preglede, pok_na_preglede + trenutni_br_pregleda,
            [](Pregled *p1, Pregled *p2) { return Pregled::DolaziPrije(*p1, *p2); });
    delete *it;
    // pomjera sve za jedno mjesto nalijevo
    std::move(it + 1, pok_na_preglede + trenutni_br_pregleda, it);
    trenutni_br_pregleda--;
    // NOTE ovo radi funkcija move:
    //   for(auto i = it; i < pok_na_preglede + trenutni_br_pregleda -1; i++)
    //     *i = *(i + 1);
}

void Pregledi::ObrisiPregledePacijenta(const std::string &ime) {
    for (int i = 0; i < trenutni_br_pregleda; i++) {
        if (pok_na_preglede[i]->DajImePacijenta() == ime) {
            delete pok_na_preglede[i];
            for (int j = i; j < trenutni_br_pregleda - 1; j++)
                pok_na_preglede[j] = pok_na_preglede[j + 1];
            trenutni_br_pregleda--;
            i--;
        }
    }
}

void Pregledi::IspisiPregledeNaDatum(const Datum &d) const {
    std::vector<Pregled *> v;
    for (int i = 0; i < trenutni_br_pregleda; i++) {
        if (pok_na_preglede[i]->DajDatumPregleda().Ocitaj() == d.Ocitaj())
            v.push_back(pok_na_preglede[i]);
    }
    std::sort(v.begin(), v.end(), [](Pregled *p1, Pregled *p2) {
        return p1->DajVrijemePregleda().Ocitaj() <
               p2->DajVrijemePregleda().Ocitaj();
    });
    for (const auto &p : v)
        p->Ispisi();
}

void Pregledi::IspisiSvePreglede() const {
    std::vector<Pregled *> all_pregledi(pok_na_preglede,
                                        pok_na_preglede + trenutni_br_pregleda);
    std::sort(
            all_pregledi.begin(), all_pregledi.end(),
            [](Pregled *p1, Pregled *p2) { return Pregled::DolaziPrije(*p1, *p2); });
    for (const auto &el : all_pregledi)
        el->Ispisi();
}

// ugh
int main() {
    int n, choice;
    std::cout << "Unesite maksimalni broj pregleda: ";
    std::cin >> n;
    Pregledi pregledi(n);

    for (;;) {
        std::cout << "1. Registriraj Pregled" << std::endl;
        std::cout << "2. Daj Broj Pregleda" << std::endl;
        std::cout << "3. Daj Broj Pregleda Na Datum" << std::endl;
        std::cout << "4. Daj Najraniji Pregled" << std::endl;
        std::cout << "5. Obrisi Najraniji Pregled" << std::endl;
        std::cout << "6. Obrisi Preglede Pacijenta" << std::endl;
        std::cout << "7. Ispisi Preglede Na Datum" << std::endl;
        std::cout << "8. Ispisi Sve Preglede" << std::endl;
        std::cout << "9. Isprazni Kolekciju" << std::endl;
        std::cout << "10. Izlaz" << std::endl;

        std::cout << "Unesite izbor: ";
        std::cin >> choice;

        if (choice == 10) {
            std::cout << "Kraj programa.";
            break;
        }

        switch (choice) {
            case 1: {
                int d, m, g, sati, minute;
                std::string i;
                std::cout << "Unesite ime pacijenta: ";
                std::cin.ignore(1000, '\n');
                std::getline(std::cin, i);

                std::cout << "Unesite datum i vrijeme pregleda (dan mjesec godina sati "
                             "minute): ";
                std::cin >> d >> m >> g >> sati >> minute;
                try {
                    pregledi.RegistrirajPregled(i, d, m, g, sati, minute);
                } catch (const std::range_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "Ukupan broj pregleda: " << pregledi.DajBrojPregleda()
                          << std::endl;
                break;
            }
            case 3: {
                std::cout << "Unesite datum (dan mjesec godina): ";
                int d, m, g;
                std::cin >> d >> m >> g;
                try {
                    Datum dat(d, m, g);
                    std::cout << "Broj pregleda na datum: "
                              << pregledi.DajBrojPregledaNaDatum(dat) << std::endl;
                } catch (const std::domain_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 4: {
                try {
                    Pregled pregled = pregledi.DajNajranijiPregled();
                    pregled.Ispisi();
                } catch (const std::domain_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 5: {
                try {
                    pregledi.ObrisiNajranijiPregled();
                    std::cout << "Najraniji pregled je obrisan." << std::endl;
                } catch (const std::range_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 6: {
                std::cout << "Unesite ime pacijenta: ";
                std::string ime;
                std::cin.ignore(10000, '\n');
                std::getline(std::cin, ime);
                pregledi.ObrisiPregledePacijenta(ime);
                std::cout << "Pregledi za pacijenta " << ime << " su obrisani.\n";
                break;
            }
            case 7: {
                std::cout << "Unesite datum: ";
                int d, m, g;
                std::cin >> d >> m >> g;
                try {
                    Datum dat(d, m, g);
                    pregledi.IspisiPregledeNaDatum(dat);
                } catch (const std::domain_error &err) {
                    std::cout << err.what() << std::endl;
                }
                break;
            }
            case 8: {
                std::cout << "Svi pregledi:\n";
                pregledi.IspisiSvePreglede();
                break;
            }
            case 9: {
                pregledi.IsprazniKolekciju();
                std::cout << "Kolekcija ispraznjena." << std::endl;
                break;
            }
            case 10: {
                std::cout << "Kraj programa.";
                break;
            }
            default: {
                std::cout << "Kraj programa.\n";
                break;
            }
        }
    }

    return 0;
}