#include <iostream>
#include <functional>

std::function<int(int)> IteriranaFunkcija(std::function<int(int)> f, int n) {
    return [=](int x) {
        // todo: if(n<=0)...
        int res = 0;
        for (int i = 0; i < n; i++) res += f(x);
        return res;
    };
}

int main() {
    auto g = IteriranaFunkcija([](int p) { return p * p; }, 10);
    std::cout << g(5);
    return 0;
}
