#include <iostream>
#include <algorithm>
#include <stdexcept>

template<typename T>
class Stek {
private:
    int broj_elemenata;
    int kapacitet;
    T *elementi;

    void Realociraj(int novi_kapacitet);

    void Test() { if (DaLiJePrazan()) throw std::logic_error("Stek je prazan"); }

public:
    Stek() : broj_elemenata(0), kapacitet(10), elementi(new T[10]) {}

    Stek(const Stek &s);

    Stek(Stek &&s) noexcept;

    Stek &operator=(const Stek &s);

    Stek &operator=(Stek &&s) noexcept;

    ~Stek() { delete[] elementi; }

    void DodajNaVrh(const T &element);

    int DajVelicinu() const { return broj_elemenata; }

    bool DaLiJePrazan() const { return broj_elemenata == 0; }

    T &DajVrh();

    const T &DajVrh() const;

    void SkiniSaVrha();

    void Ispisi() const;
};

template<typename T>
void Stek<T>::Ispisi() const {
    for (int i = 0; i < broj_elemenata; i++) std::cout << elementi[i] << " ";
    std::cout << std::endl;
}

template<typename T>
T &Stek<T>::DajVrh() {
    Test();
    return elementi[broj_elemenata - 1];
}

template<typename T>
const T &Stek<T>::DajVrh() const {
    Test();
    return elementi[broj_elemenata - 1];
}

template<typename T>
void Stek<T>::DodajNaVrh(const T &element) {
    if (broj_elemenata == kapacitet) Realociraj(2 * kapacitet);
    elementi[broj_elemenata++] = element;
}

template<typename T>
void Stek<T>::SkiniSaVrha() {
//    Test();
//    erase(elementi[broj_elemenata - 1]);
//    broj_elemenata--;
    if (DaLiJePrazan()) return;
    broj_elemenata--;
    if (broj_elemenata == int(0.3 * kapacitet) && kapacitet > 10)
        Realociraj(int(0.5 * kapacitet));
}

template<typename T>
void Stek<T>::Realociraj(int novi_kapacitet) {
    T *novi_elementi = new T[novi_kapacitet];
    for (int i = 0; i < broj_elemenata; i++) novi_elementi[i] = elementi[i];
    delete[] elementi;
    elementi = novi_elementi;
    kapacitet = novi_kapacitet;
}

template<typename T>
Stek<T>::Stek(const Stek &s) : broj_elemenata(s.broj_elemenata), kapacitet(s.kapacitet),
                               elementi(new T[s.broj_elemenata]) {
    for (int i = 0; i < s.broj_elemenata; i++) elementi[i] = s.elementi[i];
}

template<typename T>
Stek<T>::Stek(Stek &&s) noexcept : broj_elemenata(s.broj_elemenata), kapacitet(s.kapacitet), elementi(s.elementi) {
    s.broj_elemenata = 0;
    s.kapacitet = 0;
    s.elementi = nullptr;
}

template<typename T>
Stek<T> &Stek<T>::operator=(const Stek &s) {
    if (this == &s) return *this;
    if (kapacitet < s.broj_elemenata ||
        s.broj_elemenata < 0.8 * kapacitet) { // < 0.8 * kapacitet da bi se izbjeglo cesto realociranje
        Realociraj(s.broj_elemenata);
    } else
        std::copy(s.elementi, s.elementi + s.broj_elemenata, elementi);
    broj_elemenata = s.broj_elemenata;
    kapacitet = s.kapacitet;
    return *this;
}

template<typename T>
Stek<T> &Stek<T>::operator=(Stek<T> &&s) noexcept {
    if (this == &s) return *this;
    delete[] elementi;
    broj_elemenata = s.broj_elemenata;
    kapacitet = s.kapacitet;
    elementi = s.elementi;
    s.elementi = nullptr;
    // we could have done this using swap as well:
    // std::swap(broj_elemenata, s.broj_elemenata);
    // std::swap(kapacitet, s.kapacitet);
    // std::swap(elementi, s.elementi);
    return *this;
}


int main() {
    Stek<int> s1;
    for (int i = 0; i < 10; i++) s1.DodajNaVrh(i);
    std::cout << "Dodano prvih 10 elemenata na stek: ";
    s1.Ispisi();

    s1.SkiniSaVrha();
    std::cout << "Skidanje sa vrha: ";
    s1.Ispisi();

    std::cout << "Trenutni vrh steka: " << s1.DajVrh() << std::endl;

    s1.SkiniSaVrha();
    std::cout << "Broj elemenata nakon ponovnog skidanja s1 vrha: " << s1.DajVelicinu() << std::endl;

    Stek<int> s2(s1);
    std::cout << "Elementi s2 nakon upotrebe kopirajuceg konstruktora s1: ";
    s2.Ispisi();

    Stek<int> s3;
    s3 = s2;
    std::cout << "Elementi s3 nakon upotrebe kopirajuceg operatora dodjele s2: ";
    s3.Ispisi();

    Stek<int> s4(std::move(s3));
    std::cout << "Elementi s4 nakon upotrebe pomjerajuceg konstruktora s3: ";
    s4.Ispisi();

    Stek<int> s5;
    s5 = std::move(s4);
    std::cout << "Elementi s5 nakon upotrebe pomjerajuceg operatora dodjele s4: ";
    s5.Ispisi();

    return 0;
}