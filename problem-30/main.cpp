#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <vector>

class Berza {
private:
    std::vector<int> cijene;
    int min_cijena;
    int max_cijena;

public:
    Berza(int min, int max) : min_cijena(min), max_cijena(max) {
        if (min > max || min < 0 || max < 0)
            throw std::range_error("Ilegalne granicne cijene");
    }

    explicit Berza(int max) : min_cijena(0), max_cijena(max) {
        if (max < 0)
            throw std::range_error("Ilegalne granicne cijene");
    }

    void RegistrirajCijenu(int cijena);
    int DajBrojRegistriranihCijena() const { return cijene.size(); }
    void BrisiSve() { cijene.clear(); }
    int DajMinimalnuCijenu() const;
    int DajMaksimalnuCijenu() const;
    bool operator!() const { return cijene.empty(); }
    int DajBrojCijenaVecihOd(int cijena) const;
    void Ispisi() const;
    int operator[](int indeks) const;
    Berza &operator++();
    Berza operator++(int) {
        Berza b_temp(*this);
        ++(*this);
        return b_temp;
    }
    Berza &operator--();
    Berza operator--(int);
    friend Berza operator+(Berza b, int y);
    friend Berza operator+(int y, const Berza &b);
    friend Berza operator-(Berza b, int y);
    friend Berza operator-(int y, Berza b);
    friend Berza operator+(Berza b1, Berza b2);
    friend Berza operator-(Berza b1, Berza b2);
    Berza &operator+=(const Berza &nova_berza);
    Berza &operator+=(int y);
    Berza &operator-=(const Berza &nova_berza);
    Berza &operator-=(int y);
    friend bool operator==(const Berza &b1, const Berza &b2);
    friend bool operator!=(const Berza &b_1, const Berza &b_2);
};

void Berza::RegistrirajCijenu(int cijena) {
    if (cijena < min_cijena || cijena > max_cijena)
        throw std::range_error("Ilegalna cijena");
    cijene.push_back(cijena);
}

int Berza::DajMinimalnuCijenu() const {
    if (cijene.empty())
        throw std::range_error("Nema registriranih cijena");
    return *std::min_element(cijene.begin(), cijene.end());
}

int Berza::DajMaksimalnuCijenu() const {
    if (cijene.empty())
        throw std::range_error("Nema registriranih cijena");
    return *std::max_element(cijene.begin(), cijene.end());
}

int Berza::DajBrojCijenaVecihOd(int cijena) const {
    return std::count_if(
            cijene.begin(), cijene.end(),
            std::bind(std::greater<int>(), std::placeholders::_1, cijena));
}

void Berza::Ispisi() const {
    std::vector<int> kopija_cijene = cijene;
    //   std::sort(kopija_cijene.rbegin(), kopija_cijene.rend());
    std::sort(kopija_cijene.begin(), kopija_cijene.end(), std::greater<int>());
    std::transform(
            kopija_cijene.begin(), kopija_cijene.end(),
            std::ostream_iterator<double>(
                    std::cout << std::setprecision(2) << std::fixed, "\n"),
            std::bind(std::divides<double>(), std::placeholders::_1, 100.));

    // std::copy(kopija_cijene.begin(), kopija_cijene.end(),
    //           std::ostream_iterator<int>(std::cout, " "));
    // std::cout << std::endl;
}

int Berza::operator[](int indeks) const {
    if (indeks < 0 || indeks >= cijene.size())
        throw std::range_error("Neispravan indeks");
    return cijene[indeks];
}

Berza &Berza::operator++() {
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::greater<int>(), std::placeholders::_1,
                               max_cijena - 100)) != cijene.end())
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(cijene.begin(), cijene.end(), cijene.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, 100));
    return *this;
}

Berza &Berza::operator--() {
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::less<int>(), std::placeholders::_1,
                               min_cijena + 100)) != cijene.end())
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(cijene.begin(), cijene.end(), cijene.begin(),
                   std::bind(std::minus<int>(), std::placeholders::_1, 100));
    return *this;
}

Berza Berza::operator--(int) {
    Berza b_temp(*this);
    --(*this);
    return b_temp;
}

Berza operator+(Berza b, int y) {
    // vraca novu berzu
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, y));
    if (std::find_if(b.cijene.begin(), b.cijene.end(),
                     std::bind(std::greater<int>(), std::placeholders::_1,
                               b.max_cijena)) != b.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return b;
}

Berza operator+(int y, const Berza &b) {
    //   std::cout << "cigla";
    return b + y;
}

Berza operator-(Berza b, int y) {
    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(),
                   std::bind(std::minus<int>(), std::placeholders::_1, y));
    if (std::find_if(b.cijene.begin(), b.cijene.end(),
                     std::bind(std::less<int>(), std::placeholders::_1,
                               b.min_cijena)) != b.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");

    return b;
}

Berza operator-(int y, Berza b) {
    if (std::find_if(b.cijene.begin(), b.cijene.end(),
                     std::bind(std::less<int>(), y - b.min_cijena,
                               std::placeholders::_1)) != b.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");

    if (std::find_if(b.cijene.begin(), b.cijene.end(),
                     std::bind(std::greater<int>(), y - b.max_cijena,
                               std::placeholders::_1)) != b.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");

    std::transform(b.cijene.begin(), b.cijene.end(), b.cijene.begin(),
                   std::bind(std::minus<int>(), y, std::placeholders::_1));
    return b;
}

Berza operator-(Berza b1, Berza b2) {
    if (b1.cijene.size() != b2.cijene.size() || b1.min_cijena != b2.min_cijena ||
        b1.max_cijena != b2.max_cijena) {
        throw std::domain_error("Nesaglasni operandi");
    }

    std::transform(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin(),
                   b1.cijene.begin(), std::minus<int>());

    if (std::find_if(b1.cijene.begin(), b1.cijene.end(),
                     std::bind(std::less<int>(), std::placeholders::_1,
                               b1.min_cijena)) != b1.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return b1;
}

Berza operator+(Berza b1, Berza b2) {
    if (b1.cijene.size() != b2.cijene.size() || b1.min_cijena != b2.min_cijena ||
        b1.max_cijena != b2.max_cijena) {
        throw std::domain_error("Nesaglasni operandi");
    }

    std::transform(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin(),
                   b1.cijene.begin(), std::plus<int>());

    if (std::find_if(b1.cijene.begin(), b1.cijene.end(),
                     std::bind(std::greater<int>(), std::placeholders::_1,
                               b1.max_cijena)) != b1.cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return b1;
}

Berza &Berza::operator+=(const Berza &nova_berza) {
    if (cijene.size() != nova_berza.cijene.size() ||
        min_cijena != nova_berza.min_cijena ||
        max_cijena != nova_berza.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    std::transform(cijene.begin(), cijene.end(), nova_berza.cijene.begin(),
                   cijene.begin(), std::plus<int>());
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::greater<int>(), std::placeholders::_1,
                               max_cijena)) != cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    // std::transform(cijene.begin(), cijene.end(), nova_berza.cijene.begin(),
    //                cijene.begin(), [this](int cijena, int druga_cijena) {
    //                  int nc = cijena + druga_cijena;
    //                  if (nc < min_cijena || nc > max_cijena)
    //                    throw std::range_error(
    //                        "Prekoracen dozvoljeni opseg cijena");
    //                  return nc;
    //                });
    return *this;
}

Berza &Berza::operator+=(int y) {
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::greater<int>(), std::placeholders::_1,
                               max_cijena - y)) != cijene.end())
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(cijene.begin(), cijene.end(), cijene.begin(),
                   std::bind(std::plus<int>(), std::placeholders::_1, y));
    return *this;
}

// TODO
Berza &Berza::operator-=(const Berza &nova_berza) {
    if (cijene.size() != nova_berza.cijene.size() ||
        min_cijena != nova_berza.min_cijena ||
        max_cijena != nova_berza.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    std::transform(cijene.begin(), cijene.end(), nova_berza.cijene.begin(),
                   cijene.begin(), std::minus<int>());
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::less<int>(), std::placeholders::_1,
                               min_cijena)) != cijene.end())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    // std::transform(cijene.begin(), cijene.end(), nova_berza.cijene.begin(),
    //                cijene.begin(), [this](int cijena, int druga_cijena) {
    //                  int nc = cijena + druga_cijena;
    //                  if (nc < min_cijena || nc > max_cijena)
    //                    throw std::range_error(
    //                        "Prekoracen dozvoljeni opseg cijena");
    //                  return nc;
    //                });
    return *this;
}

Berza &Berza::operator-=(int y) {
    if (std::find_if(cijene.begin(), cijene.end(),
                     std::bind(std::less<int>(), std::placeholders::_1,
                               min_cijena + y)) != cijene.end())
        throw std::range_error("Prekoracen dozvoljeni opseg cijena");
    std::transform(cijene.begin(), cijene.end(), cijene.begin(),
                   std::bind(std::minus<int>(), std::placeholders::_1, y));
    return *this;
}

bool operator==(const Berza &b_1, const Berza &b_2) {
    return b_1.cijene.size() == b_2.cijene.size() &&
           b_1.min_cijena == b_2.min_cijena && b_1.max_cijena == b_2.max_cijena &&
           std::equal(b_1.cijene.begin(), b_1.cijene.end(), b_2.cijene.begin());
}

bool operator!=(const Berza &b_1, const Berza &b_2) { return !(b_1 == b_2); }

int main() {
    Berza B(100, 500);
    B.RegistrirajCijenu(300);
    Berza nova = B;

    try {
        nova = nova + 150;
        std::cout << "Nove cijene nakon dodavanja 150: ";
        nova.Ispisi();
    } catch (const std::domain_error &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    try {
        nova = nova - 150;
        std::cout << "Nove cijene nakon oduzimanja 150: ";
        nova.Ispisi();
    } catch (const std::domain_error &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    try {
        Berza nova = B + 300;
        std::cout << "Nove cijene nakon dodavanja 300: ";
        nova.Ispisi();
    } catch (const std::domain_error &e) {
        std::cout << "Izuzetak: " << e.what() << std::endl;
    }
    return 0;
}