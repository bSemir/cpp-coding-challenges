#include <iostream>
#include <vector>

void DodajSuprotne(std::vector<int> &v) {
    if (v.empty()) return;
    for (int i = 0; i < v.size(); i++) {
        v.insert(v.begin() + 1 + i, -v.at(i));
        i++; // IMPORTANT! Skip over the element we've just inserted
    }
}

int main() {
    std::cout << "Koliko ima brojeva: ";
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Unesite brojeve: ";
    for (auto &e: v) std::cin >> e;

    DodajSuprotne(v);
    for (int i = 0; i < v.size(); i++) std::cout << v[i] << " ";
    return 0;
}

// NOTE:
// We could also do it like this where we loop backwards to avoid indexing problems (when we insert negated number
// behind current number, original elements don't shift before we come to them since we are looping from behind):
// int originalSize = v.size();
// for(int i = originalSize - 1; i >= 0; i--) {
//     int suprotni = -v.at(i);
//       v.insert(v.begin() + i + 1, suprotni);
// }