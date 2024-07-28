#include <iostream>
#include <string>
#include <stdexcept>

void fun(const std::string &s, std::string &operand1, std::string &operand2, char &znak) {
    for (int i = 0; i < s.length() / 2; i++) {
        if (isdigit(s.at(i)) || s.at(i) == '.') operand1.push_back(s[i]);
        // TODO: check if string contains letters
        // else if (!isdigit(s.at(i)) && s.at(i) != ' ') throw std::domain_error("Nelegalan izraz");
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            znak = s.at(i);
            // TODO: check if the second one is negative
            for (int j = i + 1; j < s.length(); j++) {
                if (s.at(j) != ' ') operand2.push_back(s[j]);
            }
        }

    }
}

double f(const std::string &s) {
    std::string operand1, operand2;
    char znak;
    fun(s, operand1, operand2, znak);
    int pos1 = operand1.find('.');
    int pos2 = operand2.find('.');

    int result_int;
    bool is_int = false;
    double result_double;
    bool is_double = false;
    if (pos1 == -1 && pos2 == -1) {
        is_int = true;
        if (znak == '+')
            result_int = std::stoi(operand1) + std::stoi(operand2);
        else if (znak == '-')
            result_int = std::stoi(operand1) - std::stoi(operand2);
        else if (znak == '*')
            result_int = std::stoi(operand1) * std::stoi(operand2);
        else
            result_int = std::stoi(operand1) / std::stoi(operand2);
    } else {
        is_double = true;
        if (znak == '+')
            result_double = std::stod(operand1) + std::stod(operand2);
        else if (znak == '-')
            result_double = std::stod(operand1) - std::stod(operand2);
        else if (znak == '*')
            result_double = std::stod(operand1) * std::stod(operand2);
        else
            result_double = std::stod(operand1) / std::stod(operand2);
    }

    std::cout << "pos2: " << pos2 << "\n";
    std::cout << "PRVI: " << operand1 << "\n";
    std::cout << "ZNAK: " << znak << "\n";
    std::cout << "DRUGI: " << operand2 << "\n";

    if (is_int) return result_int;
    return result_double;
}

int main() {
    try {
//        std::string s = "15+172"; // ok
        std::string s = "2.5          - 3.12"; // ok
//        std::string s = " 3.7 *8.0 "; // ok
        double r = f(s);
        std::cout << "Rezultat aritmetickog izraza: " << r << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
    return 0;
}