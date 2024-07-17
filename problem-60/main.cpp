#include <iostream>
#include <functional>

auto plus2(double x) {
    return [x](double y) {
        return x + y;
    };
}

auto plus3(double x) {
    return [x](double y) {
        return [x, y](double z) {
            return x + y + z;
        };
    };
}

int main() {
    std::cout << plus2(7.7)(7.7);
    std::cout << std::endl;
    std::cout << plus3(7.7)(7.7)(7.7);
    std::cout << std::endl;
    return 0;
}