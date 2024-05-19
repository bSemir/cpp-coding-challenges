#include <iostream>
#include <list>
#include <vector>

std::vector<int> Razbrajanje(int N, int M) {
    std::list<int> distrikti;
    for (int i = 1; i <= N; ++i)
        distrikti.push_back(i);

    std::vector<int> redoslijed_redukcija;
    auto it = distrikti.begin();

    while(!distrikti.empty()) {
        for(int i = 1; i <= M; ++i) {
            ++it;
            if(it == distrikti.end())
                it = distrikti.begin();

        }
        redoslijed_redukcija.push_back(*it);
        it = distrikti.erase(it);
        if(it == distrikti.end() && !distrikti.empty()) {
            it = distrikti.begin();
        }
    }
    return redoslijed_redukcija;
}

int OdabirKoraka(int N, int K) {
    for (int M = 1; M <= N; ++M) {
        std::vector<int> redoslijed = Razbrajanje(N, M);
        // da li je distr K posljednji eliminisan
        if (redoslijed.back() == K)
            return M;
    }
    return 0;
}

int main() {
    int N, K;
    std::cout << "Unesite broj distrikta u gradu: ";
    std::cin >> N;

    std::cout << "Unesite redni broj distrikta u kojem se nalazi restoran: ";
    std::cin >> K;

    int M = OdabirKoraka(N, K);

    if (M != 0)
        std::cout << "Trazeni korak: " << M << std::endl;
    else
        std::cout << "Nije pronadjen odgovarajuci korak\n";
    return 0;
}
