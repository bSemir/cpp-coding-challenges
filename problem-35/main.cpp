#include <iostream>

template<typename T>
class Stek {
private:
    int broj_elemenata;
    int kapacitet;
    T *elementi;
public:
    Stek() : broj_elemenata(0), kapacitet(10), elementi(new T[10]) {}

    Stek(const Stek &s);

    Stek(Stek &&s);

    Stek &operator=(const Stek &s);

    Stek &operator=(Stek &&s);

    ~Stek() { delete[] elementi; }

    void DodajNaVrh(const T &element);

    int DajVelicinu() const { return broj_elemenata; }

    bool DaLiJePrazan() const { return broj_elemenata == 0; }

    T &DajVrh();

    const T &DajVrh() const;

    void SkiniSaVrha();
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
