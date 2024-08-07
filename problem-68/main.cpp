#include <iostream>

int main() {
    // 1
    int a[]{5, 1, 6, 4, 2, 3}, *m = &a[3], &n = *m;
    m += 3;
    std::cout << n;

    std::cout << std::endl;

    // 2
    int b[]{5, 1, 4, 3, 8, 6};
    for (int k: b) k *= 2;
    for (int &k: b) k += 2;
    for (int k: b) std::cout << k << " ";
    return 0;
}

// ### 1 ###
// Output: 4
// Explanation:
// m points to the 4th element of the array a, which is 4. n is a reference to *m, so n is 4.
// After m += 3, m points to the 7th element of the array a, which is out of bounds. However, n is still 4, so the output is 4.

// Addition:
// If we change `m += 3` to `*m += 3`, the output will be 7. This is because we are incrementing the value at the memory location pointed by m by 3.
// In this case it's 4 + 3 = 7.

// ### 2 ###
// Output: 7 3 6 5 10 8
// Explanation:
// The first range-based for loop does not modify the elements of the array b, because k is a copy of the elements.
// The second range-based for loop modifies the elements of the array b by adding 2 to each element. This is because `k` is a reference to the elements.
// The third range-based for loop prints the modified elements of the array `b`.