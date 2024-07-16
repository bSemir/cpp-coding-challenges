#include <iostream>
#include <algorithm>
#include <stdexcept>

int daj_broj_elemenata(int n) {
    int br = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++) br++;
    }
    return br;
}

char **alokacija(int n, char **&druga) {
    if (n <= 0) throw std::range_error("Pogresan parametar");

    char **prva{};
    int x = daj_broj_elemenata(n);
    bool flag = false;

    try {
        prva = new char *[n];
        prva[0] = new char[x];
        for (int i = 0; i < n; i++) {
            if (i != 0) {
                prva[i] = prva[i - 1] + i + 1;
                std::fill(prva[i - 1], prva[i] + i + 1, '*');
            }
        }

        druga = new char *[n];
        for (int i = 0; i < n; i++) {
            druga[i] = new char[i + 1];
            flag = true;
            std::fill(druga[i], druga[i] + 1 + i, '*');
        }
    } catch (...) {
        if (!flag)
            for (int i = 0; i < n; i++) delete[] druga[i];
        delete[] prva;
        delete[] druga;
        throw std::range_error("Kreiranje nije uspjelo!");
    }
    return prva;
}

int main() {
    try {
        std::cout << "Unesite n: ";
        int n;
        std::cin >> n;
        char **druga{};
        char **mat = alokacija(n, druga);
        if (!mat) std::cout << "Neuspjesna alokacija!";

        // ispis prve
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i + 1; j++) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }

        // ispis druge
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < i + 1; j++) {
                std::cout << druga[i][j] << " ";
            }
            std::cout << std::endl;
        }

//        for (int i = 0; i < n; i++) delete[] mat[i];
//        delete[]mat;
    } catch (const std::range_error &e) {
        std::cout << "Exception: " << e.what() << std::endl;

    }

    return 0;
}

// n = 4 -> 10
//*
//**
//***
//****

// n = 5 -> 15
//*
//**
//***
//****
//*****

// n = 6 -> 21
//*
//**
//***
//****
//*****
//******