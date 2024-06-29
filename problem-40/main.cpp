#include <iostream>

class StedniRacun {
private:
    int broj_racuna;
    double stanje_racuna;
    static int posljednji_br_racuna;
public:
    // brojevi racuna se generisu automatski, od 1001 nadalje
};

int StedniRacun::posljednji_br_racuna = 1000;