#include <iostream>
#include <stdexcept>

class StedniRacun {
private:
    double stanje_racuna;
public:
    // constructor with initialization list
    StedniRacun(double stanje_racuna = 0) : stanje_racuna(stanje_racuna) {
        if(stanje_racuna < 0) throw std::logic_error("Nedozvoljeno pocetno stanje");
    }
    StedniRacun &Ulozi(double iznos);
    StedniRacun &Podigni(double iznos);
    StedniRacun &ObracunajKamatu(double kamata);
    double DajStanje() const { return stanje_racuna; }
};

StedniRacun &StedniRacun::Ulozi(double iznos) {
//    if(iznos < 0) throw std::logic_error("Nedozvoljena transakcija(ulog je negativan)");
//    stanje_racuna += iznos;
//    return *this;
    return Podigni(-iznos);
}

StedniRacun &StedniRacun::Podigni(double iznos) {
    if(iznos > stanje_racuna) throw std::logic_error("Transakcija odbijena");
    stanje_racuna -= iznos;
    return *this;
}

StedniRacun &StedniRacun::ObracunajKamatu(double kamata){
    if(kamata < 0) throw std::logic_error("Nedozvoljena kamatna stopa");
    stanje_racuna += stanje_racuna * kamata / 100; // / 100 jer je kamata u procentima
    return *this;
}

// generic function to test if proper exception is thrown. Full type deduction used
template <typename exception_type, typename function_type>
void testException(function_type action) {
    try {
        action();
    } catch (exception_type &e) {
        std::cout << e.what() << "\n";
    }
}

int main() {
    StedniRacun s1;
    StedniRacun s2(100);
    StedniRacun s3 = 30;
    std::cout << "(s1, s2, s3): " << s1.DajStanje() << " " << s2.DajStanje() << " " << s3.DajStanje() << "\n"; // 0 100 30
    s1.Ulozi(30); s2.Ulozi(5); s3.Ulozi(20);
    std::cout << "(s1, s2, s3): " << s1.DajStanje() << " " << s2.DajStanje() << " " << s3.DajStanje() << "\n"; // 30 105 50
    s1.Ulozi(20); s2.Podigni(50);
    std::cout << "(s1, s2): " << s1.DajStanje() << " " << s2.DajStanje() << " " << std::endl; // 50 55

    s1.Ulozi(-20); s2.Podigni(-50);
    std::cout << "(s1, s2): " << s1.DajStanje() << " " << s2.DajStanje() << " " << std::endl; // 30 105

    s1.ObracunajKamatu(5);
    std::cout << "Nakon kamate od 5%: " << s1.DajStanje() << std::endl; // 31.5

    s1 = 100;
    std::cout << "(s1) +50, -20: " << s1.Ulozi(50).Podigni(20).DajStanje() << std::endl; // 130

    std::cout << s1.ObracunajKamatu(5).DajStanje() << "\n"; // 136.5

    std::cout << StedniRacun(80).Ulozi(30).DajStanje() << std::endl; // 110

    const StedniRacun s4 = s3; // s3 is 50 here
    std::cout << "s4: " << s4.DajStanje() << std::endl; // 50

    testException<std::logic_error>([]() { StedniRacun s5(-30); });
    testException<std::logic_error>([&]() { s1.Podigni(1000); });
    testException<std::logic_error>([&]() { s1.ObracunajKamatu(-5); });
    testException<std::logic_error>([&]() { s1.Ulozi(-1000); });

    return 0;
}
