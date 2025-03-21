#include <iostream>
using namespace std;

// function to calculate the sum of digits of a number
int digit_sum(string num) {
    int sum = 0;
    for (char digit : num) {
        sum += digit - '0';  // convert char to int
    }
    return sum;
}

// function to perform big integer exponentiation and return result as string
string power(int base, int exp) {
    string result = "1";

    for (int i = 0; i < exp; i++) {
        int carry = 0;
        for (int j = result.size() - 1; j >= 0; j--) {
            int product = (result[j] - '0') * base + carry;
            result[j] = (product % 10) + '0';
            carry = product / 10;
        }
        while (carry > 0) {
            result.insert(result.begin(), (carry % 10) + '0');
            carry /= 10;
        }
    }
    return result;
}

int main() {
    int max_sum = 0;

    for (int a = 1; a < 100; a++) {
        for (int b = 1; b < 100; b++) {
            string result = power(a, b);
            int sum = digit_sum(result);
            if (sum > max_sum) {
                max_sum = sum;
            }
        }
    }

    cout << max_sum << endl;
    return 0;
}
