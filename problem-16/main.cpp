#include <iostream>

class NeobicnaKlasa {
private:
    int x;
public:
    explicit NeobicnaKlasa(int x) : x(x) {
        std::cout << "Direktna inicijalizacija" << std::endl;
    }
    NeobicnaKlasa(double x) : x(x) {
        std::cout << "Kopirajuca inicijalizacija" << std::endl;
    }
};

int main() {
    NeobicnaKlasa k1(5);
    NeobicnaKlasa k2 = 5;
//    NeobicnaKlasa k3 = NeobicnaKlasa(5);
//    NeobicnaKlasa k4{5};
    return 0;
}
