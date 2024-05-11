#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <iomanip>

std::queue<bool> RotirajKoloneMatrice(std::list<std::list<double>> &matrica) {
    std::queue<bool> result_queue;
    auto first_row_size = matrica.begin()->size();
    for(auto &row : matrica) {
        if(row.size() != first_row_size)
            throw std::domain_error("Parametar nema formu matrice!");
        double p = 1;
        for(double e : row) p *= e; // proizvod elemenata tekuceg reda matrice
        result_queue.push(p > 0); // ako je proizvod pozitivan, dodaje se true u red

        // NOTE: rotate is called for each row(list) in the matrix
        auto start = row.begin();
        std::rotate(row.begin(), ++start, row.end());
    }
    return result_queue;
}

int main() {
    std::cout << "Unesite broj redova: ";
    int m;
    std::cin >> m;
    std::cout << "Unesite broj kolona: ";
    int n;
    std::cin >> n;
    std::list<std::list<double>> matrica(m, std::list<double>(n)); // matrica dimenzija m x n
    std::cout << "Unesite elemente matrice: ";
    for(auto &row : matrica)
        for(double &el : row)
            std::cin >> el;

    std::queue<bool> result_q = RotirajKoloneMatrice(matrica);

    // print matrix
    std::cout << "Transformirana matrica:" << std::endl;
    for(auto &red : matrica) {
        for(double &e : red) std::cout << std::setw(8) << e;
        std::cout << std::endl;
    }

    // print result queue
    std::cout << "Rezultirajuci red: ";
    while(!result_q.empty()) {
        std::cout << std::boolalpha << result_q.front() << " ";
        result_q.pop();
    }
    return 0;
}


// 5x3
// 1         2      -3
// 1.5     2.5     3.5
// 4         5       6
// 5.5    -3.5    -5.5
// 9         8       7

// nakon rotacije
//    2      -3     1
//  2.5     3.5   1.5
//    5       6     4
// -3.5    -5.5   5.5
//    8       7     9