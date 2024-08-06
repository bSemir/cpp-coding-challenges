#include <iostream>

int main() {
    int a[]{5, 1, 6, 4, 2, 3}, *m = &a[3], &n = *m;
    m += 3;
    std::cout << n;
    return 0;
}

// Output: 4
// Explanation:
// m points to the 4th element of the array a, which is 4. n is a reference to *m, so n is 4.
// After m += 3, m points to the 7th element of the array a, which is out of bounds. However, n is still 4, so the output is 4.

// Addition:
// If we change `m += 3` to `*m += 3`, the output will be 7. This is because we are incrementing the value at the memory location pointed by m by 3.
// In this case it's 4 + 3 = 7.