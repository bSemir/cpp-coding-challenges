#include <iostream>
#include <map>
#include <string>

std::string ZamijeniPremaRjecniku(const std::string &s, const std::map<std::string, std::string> &mapa) {
    int i = 0; int duzina = s.size();
    std::string result;
    while(i < duzina) {
        while(i < duzina && s[i] == ' ') result += s[i++]; // dodajemo sve razmake
        std::string word;
        while(i < duzina && s[i] != ' ') word += s[i++]; // izvlacimo rijec
        auto it = mapa.find(word);
        if(it != mapa.end()) result += it->second;
        else result += word;
    }
    return result;

}

int main() {
    std::map<std::string, std::string> rjecnik{{"jabuka", "apple"}, {"da", "yes"},
                                               {"kako", "how"}, {"ne", "no"},
                                               {"majmun", "monkey"}, {"mart", "ozujak"},
                                               {"maj", "svibanj"}, {"jul", "srpanj"}};
    std::cout << ZamijeniPremaRjecniku(" kako da ne ", rjecnik) << std::endl
              << ZamijeniPremaRjecniku("danas je 8. mart a 1. maj je praznik rada", rjecnik)
              << std::endl
              << ZamijeniPremaRjecniku("davor martic ima sestre maju i juliju", rjecnik)
              << std::endl;
    return 0;
}
