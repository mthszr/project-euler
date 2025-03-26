#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// define bigint as a vector of digits stored in reverse order (least significant digit first)
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

// compare two bigints; return true if a is greater than b
bool greater_bigint(const bigint &a, const bigint &b) {
    if (a.size() != b.size()) {
        return a.size() > b.size();
    }
    // sizes are equal, compare most significant digits first
    for (int i = a.size() - 1; i >= 0; i--) {
        if (a[i] != b[i]) {
            return a[i] > b[i];
        }
    }
    return false;  // they are equal
}

// convert a bigint to a string (for debugging purposes)
string bigint_to_string(const bigint &a) {
    string s;
    for (int i = a.size() - 1; i >= 0; i--) {
        s.push_back('0' + a[i]);
    }
    return s;
}

int main() {
    // variable to hold the value of d with the largest minimal solution x
    int best_d = 0;
    bigint best_x = make_bigint_from_int(0);

    // iterate through d from 2 to 1000
    for (int d = 2; d <= 1000; d++) {
        // skip if d is a perfect square
        int r = static_cast<int>(sqrt(d));
        if (r * r == d)
            continue;

        // compute the continued fraction expansion of sqrt(d)
        int a0 = r;
        int m = 0;
        int denom = 1;
        int a = a0;
        vector<int> period;  // store the repeating part

        // use the algorithm for continued fraction expansion
        do {
            m = denom * a - m;
            denom = (d - m * m) / denom;
            a = (a0 + m) / denom;
            period.push_back(a);
        } while (a != 2 * a0);

        int period_length = period.size();
        int conv_index;
        // if period length is even, use convergent index = period_length - 1
        // if odd, use convergent index = 2 * period_length - 1
        if (period_length % 2 == 0) {
            conv_index = period_length - 1;
        } else {
            conv_index = 2 * period_length - 1;
        }

        // compute the numerator of the convergent using recurrence:
        // p[-2] = 0, p[-1] = 1, then p[i] = a[i]*p[i-1] + p[i-2]
        bigint p_minus_2 = make_bigint_from_int(0);
        bigint p_minus_1 = make_bigint_from_int(1);
        bigint p_current;

        for (int i = 0; i <= conv_index; i++) {
            int coeff;
            if (i == 0) {
                coeff = a0;
            } else {
                coeff = period[(i - 1) % period_length];
            }
            // compute p_current = coeff * p_minus_1 + p_minus_2
            bigint term = multiply_bigint(p_minus_1, coeff);
            p_current = add_bigint(term, p_minus_2);
            p_minus_2 = p_minus_1;
            p_minus_1 = p_current;
        }

        // update best solution if current x is greater than best_x
        if (greater_bigint(p_current, best_x)) {
            best_x = p_current;
            best_d = d;
        }
    }

    // output the value of d which produces the largest minimal solution in x
    cout << best_d << endl;

    return 0;
}
