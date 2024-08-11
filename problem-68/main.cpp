#include <iostream>
#include <algorithm>
#include <string>
#include <set>

std::function<int(int)> w(int x) { return [x](double y) { return 3 * x + y; }; }

template<typename T, typename F>
void f(T p, T q, F r) { while (p != q) r(*--q); }

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

    std::cout << std::endl;

    // 3
    std::string str{"a ba ab aba bab"};
    std::cout << str << " ";
    std::remove_copy(str.rbegin(), str.rend(), std::back_inserter(str), ' ');
    std::cout << str;

    std::cout << std::endl;

    // 4
    std::set<int> s;
    s.insert(6);
    s.insert(3);
    s.insert(9);
    s.insert(6);
    s.insert(1);
    s.insert(8);
    // for (auto i = s.rbegin(); i != s.rend(); i++) std::cout << (++*i)++ << " "; // syntax error, uncomment to see

    std::cout << std::endl;

    // 5
    int q = 4, r{2};
    auto z = w(q + r);
    std::cout << z(q - r);

    std::cout << std::endl;

    // 6
    int arr[]{4, 6, 1, 3, 8, 2}, r_ = 3;
    f(arr, arr + 5, [&r_](int x) {
        std::cout << x << "," << r_ << " ";
        r_ += x;
    });
    std::cout << r_;

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

// ### 3 ###
// Output: a ba ab aba bab a ba ab aba babbabababa
// Explanation:
// The string `str` is "a ba ab aba bab". First cout prints the original string.
// The `remove_copy` functions copies the elements of the string in reverse order to the end of the string, removing spaces.
// Here, reverse iterators are used to iterate over the string in reverse order. The output string becomes "a ba ab aba bab babbabababa".

// ### 4 ###
// Output: syntax error -> error: cannot assign to return value because function 'operator*' returns a const value
// Explanation:
// `(++*i)++` doesn't work because when it comes to sets, the elements are constant and cannot be modified. *i is const!
// In this case, where we loop through the set in reverse order, the elements are constant and cannot be modified.

// ### 5 ###
// Output: 20
// Explanation:
// The function `w` returns a lambda function that takes a double and returns 3 * x + y.
// x is the argument passed to `w`, y is the argument passed to the lambda function.
// z is the lambda function with x = q + r = 4 + 2 = 6.
// z(q - r) = 3 * 6 + 2 = 20. So, the output is 20.

// ### 6 ###
// Output: 8,3 3,11 1,14 6,15 4,21 25
// Explanation:
// The function `f` takes two pointers and a function as arguments.
// The function `f` iterates over the array `arr` in reverse order and calls the lambda function for each element.
// The lambda function prints the element and the value of r_ separated by a comma.
// The lambda function also increments r_ by the value of the element.
// The output shows the element, the value of r_ after incrementing, and the final value of r_ after the loop.
// r(*--q) first decrements the pointer q and then dereferences it to get the value. This is equivalent to *(--q).