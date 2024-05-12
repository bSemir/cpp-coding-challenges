#include <iostream>
#include <stdexcept>


class StedniRacun {
private:
    StedniRacun(double stanje_racuna = 0);
    double stanje_racuna;
public:
    StedniRacun Ulozi(double iznos);
    StedniRacun Podigni(double iznos);
    StedniRacun ObracunajKamatu(double kamata);
    double DajStanje() const { return stanje_racuna; }
};

// define constructor
StedniRacun::StedniRacun(double stanje_racuna) {
    // konstruktor treba omoguciti automatsku konverziju realnih brojeva u objekte tipa StedniRacun
    if(stanje_racuna < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
    this->stanje_racuna = stanje_racuna;
}

StedniRacun StedniRacun::Ulozi(double iznos) {
    if(iznos < 0) throw std::logic_error("Nedozvoljena transakcija(ulog je negativan)");
    stanje_racuna += iznos;
    return *this;
}

StedniRacun StedniRacun::Podigni(double iznos) {
    if(iznos <= stanje_racuna) stanje_racuna -= iznos;
    else throw std::logic_error("Transakcija odbijena");
    return *this;
}

StedniRacun StedniRacun::ObracunajKamatu(double kamata){
    if(kamata < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
    stanje_racuna += stanje_racuna * kamata / 100; // / 100 jer je kamata u procentima
    return *this;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
