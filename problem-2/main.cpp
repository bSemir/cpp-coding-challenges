#include <iostream>
#include <vector>


// Function to calculate the number of friendly pairs in a vector
// A friendly pair is a pair of numbers where the sum of the divisors of each number equals the other number
// @param v: a vector of integers
// @return: the number of friendly pairs in the vector
int BrojPrijateljskihParova(std::vector<int> &v);

// Function to calculate the sum of the divisors of a number
// @param n: an integer
// @return: the sum of the divisors of n
int dajSumuDjelilaca(int n);

int main() {
    std::cout << "Koliko ima brojeva: ";
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Unesite brojeve: ";
    for(int & i : v) std::cin >> i;
    std::cout << "Broj prijateljskih parova: " << BrojPrijateljskihParova(v) << "\n";
    return 0;
}

int dajSumuDjelilaca(int n) {
    int suma = 0;
    for (int i = 1; i < n; i++)
        if (n % i == 0) suma += i;
    return suma;
}

int BrojPrijateljskihParova(std::vector<int> &v) {
    int brojParova = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            int suma_i = dajSumuDjelilaca(v[i]), suma_j = dajSumuDjelilaca(v[j]);
            if (suma_i == v.at(j) && suma_j == v.at(i))
                brojParova++;
        }
    }
    return brojParova;
}
