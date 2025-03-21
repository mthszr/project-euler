#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// add two non-negative big numbers represented as strings.
string addBig(const string &a, const string &b) {
    int i = a.size() - 1, j = b.size() - 1;
    int carry = 0;
    string result = "";

    while (i >= 0 || j >= 0 || carry) {
        int digitA = (i >= 0) ? a[i] - '0' : 0;
        int digitB = (j >= 0) ? b[j] - '0' : 0;
        int sum = digitA + digitB + carry;
        carry = sum / 10;
        result.push_back('0' + (sum % 10));
        i--;
        j--;
    }

    reverse(result.begin(), result.end());
    return result;
}

// multiply a non-negative big number (as string) by 2.
string multiplyBy2(const string &a) {
    int carry = 0;
    string result = "";

    for (int i = a.size() - 1; i >= 0; i--) {
        int digit = a[i] - '0';
        int prod = digit * 2 + carry;
        carry = prod / 10;
        result.push_back('0' + (prod % 10));
    }

    while (carry) {
        result.push_back('0' + (carry % 10));
        carry /= 10;
    }

    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int count = 0;
    // the first expansion (1 + 1/2) gives 3/2.
    string numerator = "3";
    string denominator = "2";

    // iterate over 1000 expansions.
    // the first expansion is considered as iteration 1.
    for (int i = 1; i <= 1000; i++) {
        // check if the numerator has more digits than the denominator.
        if (numerator.size() > denominator.size()) {
            count++;
        }

        // next expansion:
        // new_numerator = numerator + 2 * denominator
        // new_denominator = numerator + denominator
        string twoDenom = multiplyBy2(denominator);
        string newNumerator = addBig(numerator, twoDenom);
        string newDenom = addBig(numerator, denominator);

        numerator = newNumerator;
        denominator = newDenom;
    }

    cout << count << endl;
    return 0;
}
