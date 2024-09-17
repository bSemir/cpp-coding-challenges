#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    int numberOfBeams(std::vector<std::string> &bank) {
        std::vector<int> counters(bank.size());
        int total = 0;

        for (int i = 0; i < bank.size(); i++) {
            bool hasLasers = false;
            int lasersInCurrentRow = 0;
            for (int j = 0; j < bank[i].size(); j++) {
                if (bank[i][j] == '1') {
                    lasersInCurrentRow++;
                    hasLasers = true;
                }
            }
            if (hasLasers) {
                counters.push_back(lasersInCurrentRow);
            }
        }

        for (int k = 0; k < counters.size() - 1; k++) {
            // [3, 2, 1]
            total += counters[k] * counters[k + 1];
        }

        return total;
    }
};

int main() {
    Solution solution;
    std::vector<std::string> bank = {"000", "111", "000"};
    std::cout << solution.numberOfBeams(bank) << std::endl;
    return 0;
}
