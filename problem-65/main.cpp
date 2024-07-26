#include <iostream>
#include <string>
#include <stdexcept>

void fun(const std::string &s, std::string &operand1, std::string &operand2, std::string &znak) {
    for (int i = 0; i < s.length() / 2; i++) {
        if (isalnum(s.at(i)) || s.at(i) == '.') operand1.push_back(s[i]);
    }

    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') {
            znak = s.at(i);
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
    std::string s = " 3.7 *8.0 "; // ok
    f(s);
    return 0;
}
