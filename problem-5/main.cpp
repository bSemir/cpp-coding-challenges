#include <iostream>
#include <memory>
#include <vector>

auto KreirajMatricu (int x) {
    return [x](int y) -> auto {
        try {
            auto matrix = std::make_unique<std::shared_ptr<std::vector<int>>[]>(x);
            for (int i = 0; i < x; i++) {
                matrix[i] = std::make_shared<std::vector<int>>(y, 0);
//            (*matrix[i])[i] = 1;
                for (int j = 0; j < y; j++)
                    if (i == j)
                        (*matrix[i])[j] = 1;
            }
            return matrix;
        } catch (std::bad_alloc &e) {
            std::cout << "Problemi s memorijom!" << std::endl;
        }
    };
};

int main() {
    int x = 5, y = 5;
    auto matrix = KreirajMatricu(x)(y);
    std::cout << "Ispis matrice: \n";
    for(int i = 0; i < x; i++) {
        for(int j = 0; j < y; j++) {
            std::cout << (*matrix[i])[j] << " ";  // (*matrix[i])[j] je isto sto i matrix[i]->at(j) jer je matrix[i] tipa unique_ptr<vector<int>>
        }
        std::cout << std::endl;
    }

    return 0;
}
