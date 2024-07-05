#include <iostream>
#include <cstring>


class String {
    char *niz_znakova;
    int duzina;

    void alociraj() { niz_znakova = new char[duzina + 1]{}; } // +1 za '\0'

public:
    String(const char niz[] = "") : duzina(strlen(niz)) {
        alociraj();
        strcpy(niz_znakova, niz);
    }

    String(int n, char c) {
        if (n <= 0) {
            // kreiraj prazan string
            duzina = 0;
            alociraj();
        } else {
            duzina = n;
            alociraj();
            for (int i = 0; i < duzina; i++) niz_znakova[i] = c;
            // std::fill_n(niz_znakova, n, c);
        }
    }

    ~String() { delete[] niz_znakova; }

    int DajDuzinu() const { return duzina; }
};

int main() {
    String s("Mrvim dok jedem");
    std::cout << s.DajDuzinu() << std::endl;

    String s2(7, 'a');
    std::cout << s2.DajDuzinu() << std::endl;
    return 0;
}
