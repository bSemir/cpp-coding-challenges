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

    ~String() { delete[] niz_znakova; }

    int DajDuzinu() const { return duzina; }
};

int main() {
    String s("Mrvim dok jedem");
    std::cout << s.DajDuzinu() << std::endl;
    return 0;
}
