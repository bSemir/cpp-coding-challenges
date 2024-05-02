#include <iostream>
#include <functional>

std::function<double(double)> plus2(double x) {
    return [x](double y) {
        return x + y;
    };
}

int main() {
    auto f = plus2(2);
    std::cout << f(3) << std::endl;
    return 0;
}
