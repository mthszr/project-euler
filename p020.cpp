#include <iostream>
#include <vector>

using namespace std;

// Function to calculate factorial using an array for large numbers
vector<int> calculate_factorial(int n) {
    vector<int> result(1, 1);  // Initialize result with 1

    for (int i = 2; i <= n; ++i) {
        int carry = 0;
        for (size_t j = 0; j < result.size(); ++j) {
            int product = result[j] * i + carry;
            result[j] = product % 10;  // Store the last digit
            carry = product / 10;      // Carry over the rest
        }
        while (carry > 0) {
            result.push_back(carry % 10);  // Add carry digits
            carry /= 10;
        }
    }
    return result;  // Result is stored in reverse order
}

// Function to calculate the sum of digits in the factorial
int sum_of_digits(const vector<int>& factorial) {
    int sum = 0;
    for (int digit : factorial) {
        sum += digit;
    }
    return sum;
}

int main() {
    int n = 100;
    vector<int> factorial = calculate_factorial(n);
    int sum = sum_of_digits(factorial);

    cout << "The sum of the digits in the number " << n << "! is: " << sum << endl;

    return 0;
}
