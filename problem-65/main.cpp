#include <iostream>
#include <string>
#include <stdexcept>

void fun(const std::string &s, std::string &operand1, std::string &operand2, std::string &znak) {
    for (int i = 0; i < s.length() / 2; i++) {
        if (isdigit(s.at(i)) || s.at(i) == '.') operand1.push_back(s[i]);
        else if (!isdigit(s.at(i)) && s.at(i) != ' ') throw std::domain_error("Nelegalan izraz");
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

void f(const std::string &s) {
    std::string operand1, operand2, znak;
    fun(s, operand1, operand2, znak);

    std::cout << "PRVI: " << operand1 << "\n";
    std::cout << "ZNAK: " << znak << "\n";
    std::cout << "DRUGI: " << operand2 << "\n";
}

int main() {
//    std::string s = "15+172"; // ok
//    std::string s = "2.5          - 3.12"; // ok
    try {
        std::string s = " 3.7 *8.0 "; // ok
        f(s);
    } catch (const std::domain_error &e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
