#include <cmath>
#include <iostream>
using namespace std;

// Function to return the sum of numbers that can be written as the sum of fifth powers of their digits
int sum_fifth_powers() {
    int upper_limit = 6 * pow(9, 5);  // Calculate the upper limit as 6 * 59049
    int result = 0;

    for (int num = 10; num <= upper_limit; ++num) {
        int sum = 0, temp = num;

        // Calculate the sum of fifth powers of the digits
        while (temp > 0) {
            int digit = temp % 10;
            sum += pow(digit, 5);
            temp /= 10;
        }

        // Check if the number equals the sum of fifth powers of its digits
        if (sum == num) {
            result += num;
        }
    }

    return result;
}

int main() {
    // Print the result
    cout << sum_fifth_powers() << endl;
    return 0;
}
