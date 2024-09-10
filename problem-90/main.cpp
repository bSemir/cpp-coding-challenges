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
    // TODO: Testirati implementirane funkcionalnosti
    return 0;
}