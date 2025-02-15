#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// checks if the current permutation of digits has the substring divisibility property
bool hasSubstringDivisibility(const vector<int>& digits) {
    // d2d3d4 must be divisible by 2
    int num = digits[1] * 100 + digits[2] * 10 + digits[3];
    if (num % 2 != 0) return false;

    // d3d4d5 must be divisible by 3
    num = digits[2] * 100 + digits[3] * 10 + digits[4];
    if (num % 3 != 0) return false;

    // d4d5d6 must be divisible by 5
    num = digits[3] * 100 + digits[4] * 10 + digits[5];
    if (num % 5 != 0) return false;

    // d5d6d7 must be divisible by 7
    num = digits[4] * 100 + digits[5] * 10 + digits[6];
    if (num % 7 != 0) return false;

    // d6d7d8 must be divisible by 11
    num = digits[5] * 100 + digits[6] * 10 + digits[7];
    if (num % 11 != 0) return false;

    // d7d8d9 must be divisible by 13
    num = digits[6] * 100 + digits[7] * 10 + digits[8];
    if (num % 13 != 0) return false;

    // d8d9d10 must be divisible by 17
    num = digits[7] * 100 + digits[8] * 10 + digits[9];
    if (num % 17 != 0) return false;

    return true;
}

int main() {
    // initialize the digits 0 through 9
    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    long long totalSum = 0;

    // generate all permutations of digits
    do {
        if (hasSubstringDivisibility(digits)) {
            // build the pandigital number from the digits vector
            long long num = 0;
            for (int d : digits) {
                num = num * 10 + d;
            }
            totalSum += num;
        }
    } while (next_permutation(digits.begin(), digits.end()));

    cout << totalSum << endl;
    return 0;
}
