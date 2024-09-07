#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> transform(const std::vector<int> &v) {
    std::vector<int> result;
    for (int i = 0; i < v.size(); i++) {
        int number = v[i];
        int newNumber = 0;
        int power = 0;
        if (number < 0) // if it's negative, make it positive
            number = std::abs(number);
        while (number > 0) {
            int digit = number % 10; // zadnja cifra
            if (digit % 2 == 0) {
                digit++;
            } else {
                digit--;
            }
            newNumber += digit * pow(10, power); // 10^0 = 1, 10^1 = 10, 10^2 = 100
            power++; // povecavamo stepen za 1 jer prelazimo na sljedecu cifru
            number /= 10; // skidamo zadnju cifru
        }
        result.push_back(newNumber);
    }
    return result;
}

int main() {
    std::cout << "Enter the size of the vector: ";
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    std::cout << "Enter the elements of the vector: ";
    for (int i = 0; i < n; i++)
        std::cin >> v[i];

    std::vector<int> result = transform(v);
    std::cout << "The result is: " << std::endl;
    for (int i: result)
        std::cout << i << std::endl;
    return 0;
}