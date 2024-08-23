#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

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
        if (s[i] == '%' && s[i + 1] == 'd') {
            res = res + std::to_string(int(v[j++]));
            i++;
        } else if (s[i] == '%' && s[i + 1] == 'f') {
            res = res + std::to_string(v[j++]);
            i++;
        } else {
            res = res + s[i];
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
    } catch (const std::range_error &err) {
        std::cout << err.what() << std::endl;
    }
    return 0;
}