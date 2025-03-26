#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// bigint is represented as a vector of digits in reverse order
typedef vector<int> bigint;

// create a bigint from an integer
bigint make_bigint_from_int(int x) {
    bigint result;
    if (x == 0) {
        result.push_back(0);
        return result;
    }
    while (x > 0) {
        result.push_back(x % 10);
        x /= 10;
    }
    return result;
}

// add two bigints and return the sum
bigint add_bigint(const bigint &a, const bigint &b) {
    bigint result;
    int carry = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; i++) {
        int digit_a = (i < a.size() ? a[i] : 0);
        int digit_b = (i < b.size() ? b[i] : 0);
        int sum = digit_a + digit_b + carry;
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    while (carry > 0) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    return result;
}

// multiply a bigint by an integer and return the product
bigint multiply_bigint(const bigint &a, int b) {
    bigint result;
    int carry = 0;
    for (int i = 0; i < a.size(); i++) {
        int prod = a[i] * b + carry;
        result.push_back(prod % 10);
        carry = prod / 10;
    }
    while (carry > 0) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    return result;
}

int main() {
    // number of convergents to compute
    int terms = 100;
    vector<int> a(terms);

    // first term of the continued fraction for e is 2
    a[0] = 2;
    // generate the remaining terms for e with pattern: [1, 2k, 1]
    for (int i = 1; i < terms; i++) {
        if (i % 3 == 2) {
            a[i] = 2 * ((i + 1) / 3);
        } else {
            a[i] = 1;
        }
    }

    // initialize recurrence for numerator:
    // p[-2] = 0, p[-1] = 1
    bigint p_minus_2 = make_bigint_from_int(0);
    bigint p_minus_1 = make_bigint_from_int(1);
    bigint p_current;

    // compute the numerator of each convergent using the recurrence:
    // p[i] = a[i] * p[i-1] + p[i-2]
    for (int i = 0; i < terms; i++) {
        // multiply p_minus_1 by a[i]
        bigint temp = multiply_bigint(p_minus_1, a[i]);
        // add p_minus_2 to temp to get the current numerator
        p_current = add_bigint(temp, p_minus_2);
        // update previous values for the next iteration
        p_minus_2 = p_minus_1;
        p_minus_1 = p_current;
    }

    // sum the digits in the numerator of the 100th convergent
    int digit_sum = 0;
    for (int digit : p_current) {
        digit_sum += digit;
    }

    // output the sum of digits
    cout << digit_sum << endl;

    return 0;
}
