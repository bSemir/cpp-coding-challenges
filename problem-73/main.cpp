#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>

int broj_pojavljivanja(std::string &s, const std::vector<double> &v) {
    int n = 0;
    for (int i = 0; i < s.size(); i++)
        if (s.at(i) == '%' && (s.at(i + 1) == 'd' || s.at(i + 1) == 'f')) n++;
    return n;
}

std::string fun(std::string &s, const std::vector<double> &v) {
    if (broj_pojavljivanja(s, v) > v.size()) throw std::range_error("Nedovoljno brojeva");
    std::string res;
    int j = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '%' && i + 1 < s.length()) {
            if (s[i + 1] == 'd') {
                res = res + std::to_string(int(v[j++]));
                i++;
            } else if (s[i + 1] == 'f') {
                std::ostringstream oss;
                oss << v[j++];
                res += oss.str();
                i++;
            } else {
                res = res + s[i];
            }
        } else {
            res += s[i];
        }
    }
    return res;
}

int main() {
    try {
        std::string s = "abc%dxx%fyy %d";
        std::vector<double> v{12.25, 34.13, 25, 47};
        std::string r = fun(s, v);
        std::cout << r << std::endl;
        // outputs: abc12xx34.130000yy 25
        // should be: abc12xx34.13yy 25
    } catch (const std::range_error &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}