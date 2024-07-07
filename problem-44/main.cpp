#include <iostream>
#include <cstring>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cctype>

class String {
    char *niz_znakova;
    int duzina;

    void alociraj() { niz_znakova = new char[duzina + 1]{}; } // +1 za '\0'

    String &dodijeli(const char *odakle, int koliko);

    String(int n) : duzina(n) { alociraj(); }

    void provjeri_indeks(int i) const {
        if (i < 0 || i >= duzina) throw std::range_error("Neispravan indeks");
    }

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

    String &operator+=(const String &s);

    String &operator+=(const char niz[]);

    String &operator+=(char c);

    char &operator[](int i) {
        provjeri_indeks(i);
        return niz_znakova[i];
    }

    const char &operator[](int i) const {
        provjeri_indeks(i);
        return niz_znakova[i];
    }

    std::istream &CitajCijeluLiniju(std::istream &tok, String &s);

    String operator()(int i, int j) const;

    friend String operator+(const String &s1, const String &s2);

    friend bool operator==(const String &s1, const String &s2) {
        return s1.duzina == s2.duzina && std::strcmp(s1.niz_znakova, s2.niz_znakova) == 0;
    }

    friend bool operator!=(const String &s1, const String &s2) { return !(s1 == s2); }

    friend bool operator<(const String &s1, const String &s2) {
        return std::strcmp(s1.niz_znakova, s2.niz_znakova) < 0;
    }

    friend bool operator>(const String &s1, const String &s2) {
        return std::strcmp(s1.niz_znakova, s2.niz_znakova) > 0;
        // return s2 < s1;
    }

    friend bool operator<=(const String &s1, const String &s2) { return !(s1 > s2); }

    friend bool operator>=(const String &s1, const String &s2) { return !(s1 < s2); }

    void Kapitaliziraj() { for (char &c: *this) c = std::toupper(c); }

    const char *DajCString() const { return niz_znakova; }
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

String &String::operator+=(const String &s) {
    int nova_duzina = duzina + s.duzina;
    char *novi = new char[nova_duzina + 1];
    std::strcpy(novi, niz_znakova);
    std::strcat(novi, s.niz_znakova);
    delete[] niz_znakova;
    niz_znakova = novi;
    duzina = nova_duzina;
    return *this;
}

String &String::operator+=(char c) {
    dodijeli(niz_znakova, duzina + 1); // +1 za novi znak
    niz_znakova[duzina - 1] = c;
    return *this;
}

String &String::operator+=(const char *niz) {
    if (*niz == 0) return *this;
    int stara_duzina = duzina; // cuvamo staru jer ce se promijeniti
    dodijeli(niz_znakova, duzina + strlen(niz));
    std::strcpy(niz_znakova + stara_duzina, niz); // kopiraj niz na kraj
    return *this;
}

std::istream &String::CitajCijeluLiniju(std::istream &tok, String &s) {
    tok.clear();
    tok.ignore(10000, '\n');
    s = "";
    char c;
    while ((c = tok.get()) != '\n') s += c;
    return tok;
}

String String::operator()(int i, int j) const {
    provjeri_indeks(i);
    provjeri_indeks(j);
    String s = "";
    for (int k = i; k <= j; k++) s += niz_znakova[k];
    return s;
}

String operator+(const String &s1, const String &s2) {
    if (s1.duzina == 0) return s2;
    if (s2.duzina == 0) return s1;
    String s(s1.duzina + s2.duzina);
    std::strcpy(s.niz_znakova, s1.niz_znakova);
    std::strcpy(s.niz_znakova + s1.duzina, s2.niz_znakova);
    return s;
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

    String s6;
    std::cout << "Unesite string s6: ";
    std::cin >> s6;

    std::cout << "Sadrzaj stringa s6: " << s6 << std::endl;

    s6 += s5;
    std::cout << "Sadrzaj stringa s6 nakon nadodavanja s5: " << s6 << std::endl;


    s6 += '?';
    std::cout << "Sadrzaj stringa s6 nakon nadodavanja znaka '?': " << s6 << std::endl;

    s6[0] = 'X';
    std::cout << "Sadrzaj stringa s6 nakon promjene prvog znaka: " << s6 << std::endl;

    std::cout << "Unesite string s7: ";
    String s7;
    s7.CitajCijeluLiniju(std::cin, s7);
    std::cout << "Sadrzaj stringa s7: " << s7 << std::endl;

    std::cout << "Podstring od s5 (izmedju 0 i 4): " << s5(0, 4) << std::endl; // "Hello"®

    std::cout << "Kapitaliziran string s5: ";
    s5.Kapitaliziraj();
    std::cout << s5 << std::endl;
    return 0;
}