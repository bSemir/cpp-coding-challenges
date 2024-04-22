#include <iostream>
#include <string>

std::string IzvrniRedoslijedRijeci(const std::string &s);

int main() {
    std::cout << "Enter the string: ";
    std::string s;
    std::getline(std::cin, s);
    std::cout << "Reversed string: " << IzvrniRedoslijedRijeci(s) << std::endl;
    return 0;
}

std::string IzvrniRedoslijedRijeci(const std::string &s) {
    std::string reversed;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ' ' && (i == 0 || s[i - 1] == ' ')) { // finding the beggining of the word (first word or nth word)
            std::string word;
            while (i < s.length() && s[i] != ' ') word += s[i++];
            if (reversed == "") reversed = word;
            else { reversed = word + ' ' + reversed; } // word + space + everything that was before
        }
    }
    return reversed;
}
