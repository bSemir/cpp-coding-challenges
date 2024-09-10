#include <iostream>
#include <stack>
#include <type_traits>

template<typename tip_elemenata, typename tip_funkcije>
auto TransformiraniStek(std::stack<tip_elemenata> s, tip_funkcije f) {
    // Stek za obrtanje originalnog steka
    std::stack<tip_elemenata> obrnuti;

    // prebacivanje elemenata iz originalnog steka u obrnuti stek kako bismo ocuvali redoslijed
    while (!s.empty()) {
        obrnuti.push(s.top());
        s.pop();
    }

    // novi stek u koji cemo stavljati transformisane elemente
    std::stack<std::remove_reference_t<decltype(f(obrnuti.top()))>> novi;

    // applying funkciju f na elemente obrnutog steka i punimo novi stek
    while (!obrnuti.empty()) {
        novi.push(f(obrnuti.top()));
        obrnuti.pop();
    }

    return novi;
}

int main() {
    int n;
    std::cout << "Unesite velicinu steka: ";
    std::cin >> n;

    std::stack<int> stek;
    std::cout << "Unesite elemente: ";
    for (int i = 0; i < n; i++) {
        int element;
        std::cin >> element;
        stek.push(element);
    }

    // Lambda f. koja vraca reciprocne vrijednosti
    auto reciprocal = [](int x) -> double {
        return 1.0 / x;
    };

    auto transformirani_stek = TransformiraniStek(stek, reciprocal);

    std::cout << "Stek reciprocnih vrijednosti: ";
    while (!transformirani_stek.empty()) {
        std::cout << transformirani_stek.top() << " ";
        transformirani_stek.pop();
    }
    std::cout << std::endl;
    return 0;
}