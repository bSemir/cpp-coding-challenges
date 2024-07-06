#include <iostream>
#include <cstring>


class String {
    char *niz_znakova;
    int duzina;

    void alociraj() { niz_znakova = new char[duzina + 1]{}; } // +1 za '\0'

    String &dodijeli(const char *odakle, int koliko);

public:
    String(const char niz[] = "") : duzina(strlen(niz)) {
        alociraj();
        strcpy(niz_znakova, niz);
    }

    String(int n, char c);

    String(std::initializer_list<char> lista) : duzina(lista.size()) {
        alociraj();
        int i = 0;
        for (char znak: lista) niz_znakova[i++] = znak;
        // std::copy(lista.begin(), lista.end(), niz_znakova);
    }

    String(const String &s) : duzina(s.duzina) {
        alociraj();
        strcpy(niz_znakova, s.niz_znakova);
    }

    String(String &&s) : duzina(s.duzina), niz_znakova(s.niz_znakova) { s.niz_znakova = nullptr; }

    String &operator=(const String &s) {
//        if (this == &s) return *this;
//        delete[] niz_znakova;
//        duzina = s.duzina;
//        alociraj();
//        strcpy(niz_znakova, s.niz_znakova);
//        return *this;
        return dodijeli(s.niz_znakova, s.duzina);
    }

    String &operator=(String &&s) noexcept {
        std::swap(duzina, s.duzina);
        std::swap(niz_znakova, s.niz_znakova);
        return *this;
    }

    String &operator=(const char niz[]) { return dodijeli(niz, strlen(niz)); }

    ~String() { delete[] niz_znakova; }

    int DajDuzinu() const { return duzina; }

    const char *begin() const { return niz_znakova; }

    char *begin() { return niz_znakova; }

    const char *end() const { return niz_znakova + duzina; }

    char *end() { return niz_znakova + duzina; }

    friend std::ostream &operator<<(std::ostream &tok, const String &s) { return tok << s.niz_znakova; }

    friend std::istream &operator>>(std::istream &tok, String &s);

    // TODO: Implementirati operatore +=
    String &operator+=(const String &s);

    String &operator+=(const char niz[]);

    String &operator+=(char c);
};

String &String::dodijeli(const char *odakle, int koliko) {
    if (duzina < koliko) {
        char *novi = new char[koliko + 1];
        std::strcpy(novi, odakle);
        delete[] niz_znakova;
        niz_znakova = novi;
    }
        // nema potrebe za alokacijom novog prostora (duzina >= koliko)
    else {
        std::strcpy(niz_znakova, odakle);
    }
    duzina = koliko;
    return *this; // vrati referencu na izmijenjeni objekat
}

String::String(int n, char c) {
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

std::istream &operator>>(std::istream &tok, String &s) {
    s = "";
    tok >> std::ws;
    while (!std::isspace(tok.peek())) s += tok.get();
    return tok;
}

int main() {
    String s("Mrvim dok jedem");
    std::cout << s.DajDuzinu() << std::endl; // 15

    String s2(7, 'a');
    std::cout << s2.DajDuzinu() << std::endl; // 7

    String s3{'a', 'b', 'c', 'd', 'e'};
    std::cout << s3.DajDuzinu() << std::endl; // 5

    String s4(s3);
    std::cout << s4.DajDuzinu() << std::endl; // 5

    String s5(std::move(s2));
    std::cout << s5.DajDuzinu() << std::endl; // 7

    s5 = s4;
    std::cout << s5.DajDuzinu() << std::endl; // 5

    s5 = std::move(s3);
    std::cout << s5.DajDuzinu() << std::endl; // 5

    s5 = "Hello world!";
    std::cout << s5.DajDuzinu() << std::endl; // 12

    std::cout << "Sadrzaj stringa s5: " << s5 << std::endl; // Hello world!
    return 0;
}
