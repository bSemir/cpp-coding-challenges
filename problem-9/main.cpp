#include <iostream>
#include <map>

template <typename tipElemenata>
struct Cvor {
    tipElemenata element;
    Cvor<tipElemenata> *veza;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
