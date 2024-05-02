#include <iostream>
#include <functional>

std::function<double(double)> plus2(double x) {
    return [x](double y) {
        return x + y;
    };
}

auto plus3(double x) {
    return [x](double y) {
        return [x, y](double z) { return x + y + z; };
    };
}

int main() {
    std::cout << "plus2: " << std::endl;
    auto f = plus2(2);
    std::cout << f(3) << std::endl;
    std::cout << "plus3: " << std::endl;
    auto g = plus3(2);
    std::cout << g(3)(4) << std::endl;

    // or
    // std::cout << plus2(3)(5) << std::endl;
    // std::cout << plus3(3)(5)(6) << std::endl;
    return 0;
}

// note:
// return type for plus3 is function<function<double(double)>(double)>
// line 11: return type is function<double(double)>
// line 13: return type is double