#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// abstract class
class ApstraktniStudent {
private:
    std::string ime;
    std::string prezime;
    int broj_indeksa;
    int broj_polozenih_ispita;
    double prosjek;
public:
    ApstraktniStudent(std::string ime, std::string prezime, int broj_indeksa) {
        this->ime = ime;
        this->prezime = prezime;
        this->broj_indeksa = broj_indeksa; // this zato sto je to atribut klase
        broj_polozenih_ispita = 0;
        prosjek = 5; // this nije potreban jer se ne preklapa sa parametrom
    }

    virtual ~ApstraktniStudent() {} // uvijek neophodan kad imamo polimorfizam

    std::string DajIme() const { return this->ime; }

    std::string DajPrezime() const { return this->prezime; }

    int DajBrojIndeksa() const { return this->broj_indeksa; }

    int DajBrojPolozenih() const { return this->broj_polozenih_ispita; }

    double DajProsjek() const{ return this->prosjek; }

    void RegistrirajIspit(int ocjena) {
        if (ocjena > 10 || ocjena < 5)
            throw std::domain_error("Neispravna ocjena");
        if(ocjena == 5)
            return;
//        prosjek = (prosjek + ocjena) / broj_polozenih_ispita;
        prosjek = (prosjek * broj_polozenih_ispita + ocjena) / (broj_polozenih_ispita + 1);
        broj_polozenih_ispita++;
    }

    void PonistiOcjene() {
        broj_polozenih_ispita = 0;
        prosjek = 5.0;
    }

    // pure virtual functions
    virtual void IspisiPodatke() const = 0;
    virtual ApstraktniStudent* DajKopiju() const = 0;
};

class StudentBachelor : public ApstraktniStudent {
public:
    StudentBachelor(std::string ime, std::string prezime, int broj_indeksa) : ApstraktniStudent(ime, prezime, broj_indeksa) {}

    void IspisiPodatke() const override {
        std::cout << "Student bachelor studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << " ima prosjek " << DajProsjek() << "." << std::endl;
    }

    ApstraktniStudent* DajKopiju() const override {
        return new StudentBachelor(*this);
    }
};

class StudentMaster : public ApstraktniStudent {
private:
    int godina_diplomiranja;
public:
    StudentMaster(std::string ime, std::string prezime, int broj_indeksa, int godina_diplomiranja) : ApstraktniStudent(ime, prezime, broj_indeksa) {
        this->godina_diplomiranja = godina_diplomiranja;
    }

    void IspisiPodatke() const override {
        std::cout << "Student master studija " << DajIme() << " " << DajPrezime() << ", sa brojem indeksa " << DajBrojIndeksa() << ", zavrsio bachelor studij godine " << godina_diplomiranja << ", ima prosjek " << DajProsjek() << "." << std::endl;
    }

    ApstraktniStudent* DajKopiju() const override {
        return new StudentMaster(*this);
    }
};

// p29 - class Fakultet (ti si Fakultet bokte j***)
class Fakultet {
private:
    std::vector<ApstraktniStudent*> studenti;
public:
    Fakultet() {}

    ~Fakultet();

    Fakultet(const Fakultet &f);

    Fakultet(Fakultet &&f) = default;

    Fakultet &operator =(const Fakultet &f);

    Fakultet &operator =(Fakultet &&f);

    void UpisiStudenta(std::string ime, std::string prezime, int indeks);

    void UpisiStudenta(std::string ime, std::string prezime, int indeks, int godina_diplomiranja);

    void ObrisiStudenta(int indeks);

    ApstraktniStudent &operator [](int indeks);

    const ApstraktniStudent &operator [](int indeks) const;

    void IspisiSveStudente() const;
};

template <typename TipIzuzetka, typename FunkcijskiTip>
void TestirajIzuzetak(FunkcijskiTip akcija) {
    try { akcija(); }
    catch(TipIzuzetka &e) { std::cout << e.what() << std::endl; }
}

int main() {
    StudentBachelor s1("Dusko", "Dugousko", 1234);
    s1.RegistrirajIspit(7); s1.RegistrirajIspit(6); s1.RegistrirajIspit(5);
    s1.RegistrirajIspit(10); s1.RegistrirajIspit(7);
    std::cout << s1.DajIme() << " " << s1.DajPrezime() << " " << s1.DajBrojIndeksa()
              << " " << s1.DajBrojPolozenih() << " " << s1.DajProsjek() << std::endl;
    s1.IspisiPodatke();
    TestirajIzuzetak<std::domain_error>([&]() { s1.RegistrirajIspit(4); });
    TestirajIzuzetak<std::domain_error>([&]() { s1.RegistrirajIspit(11); });
    s1.PonistiOcjene();
    std::cout << s1.DajIme() << " " << s1.DajPrezime() << " " << s1.DajBrojIndeksa()
              << " " << s1.DajBrojPolozenih() << " " << s1.DajProsjek() << std::endl;
    s1.IspisiPodatke();

    StudentMaster s2("Paja", "Patak", 4312, 2015);
    s2.RegistrirajIspit(7); s2.RegistrirajIspit(6); s2.RegistrirajIspit(5);
    s2.RegistrirajIspit(10); s2.RegistrirajIspit(7);
    std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa()
              << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
    s2.IspisiPodatke();
    TestirajIzuzetak<std::domain_error>([&]() { s2.RegistrirajIspit(4); });
    TestirajIzuzetak<std::domain_error>([&]() { s2.RegistrirajIspit(11); });
    s2.PonistiOcjene();
    std::cout << s2.DajIme() << " " << s2.DajPrezime() << " " << s2.DajBrojIndeksa()
              << " " << s2.DajBrojPolozenih() << " " << s2.DajProsjek() << std::endl;
    s2.IspisiPodatke();

    ApstraktniStudent *ps = new StudentBachelor("Dusko", "Dugousko", 1234);
    ps->RegistrirajIspit(7); ps->RegistrirajIspit(6); ps->RegistrirajIspit(5);
    ps->RegistrirajIspit(10); ps->RegistrirajIspit(7);
    std::cout << ps->DajIme() << " " << ps->DajPrezime() << " " << ps->DajBrojIndeksa()
              << " " << ps->DajBrojPolozenih() << " " << ps->DajProsjek() << std::endl;
    ps->IspisiPodatke();
    ApstraktniStudent *pskopija = ps->DajKopiju();
    pskopija->IspisiPodatke();
    delete ps; delete pskopija;

    ps = new StudentMaster("Paja", "Patak", 4312, 2015);
    ps->RegistrirajIspit(7); ps->RegistrirajIspit(6); ps->RegistrirajIspit(5);
    ps->RegistrirajIspit(10); ps->RegistrirajIspit(7);
    std::cout << ps->DajIme() << " " << ps->DajPrezime() << " " << ps->DajBrojIndeksa()
              << " " << ps->DajBrojPolozenih() << " " << ps->DajProsjek() << std::endl;
    ps->IspisiPodatke();
    pskopija = ps->DajKopiju(); pskopija->IspisiPodatke();
    delete ps; delete pskopija;

    return 0;
}