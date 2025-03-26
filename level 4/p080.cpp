#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isPerfectSquare(int n) {
    int root = static_cast<int>(sqrt(n));
    return (root * root == n);
}

string computeSqrt(int n, int decimalDigits) {
    if (n <= 0) return "0";

    string result;
    int intPart = static_cast<int>(sqrt(n));
    result += to_string(intPart);

    if (intPart * intPart == n) return result;  // Exact square

    result += ".";
    int remainder = n - intPart * intPart;

    for (int i = 0; i < decimalDigits; ++i) {
        remainder *= 100;
        int divisor = intPart * 20;
        int digit = 0;

        while ((divisor + digit + 1) * (digit + 1) <= remainder) {
            ++digit;
        }

        remainder -= (divisor + digit) * digit;
        intPart = intPart * 10 + digit;
        result += to_string(digit);
    }

    return result;
}

int sumFirst100Digits(int n) {
    string sqrtStr = computeSqrt(n, 100);
    size_t decimalPos = sqrtStr.find('.');

    int sum = 0;
    for (int i = decimalPos + 1; i < decimalPos + 101 && i < sqrtStr.size(); ++i) {
        sum += sqrtStr[i] - '0';
    }
    return sum;
}

int main() {
    int total = 0;
    for (int n = 1; n <= 100; ++n) {
        if (!isPerfectSquare(n)) {
            total += sumFirst100Digits(n);
        }
    }
    cout << "The total of the digital sums is: " << total << endl;
    return 0;
}