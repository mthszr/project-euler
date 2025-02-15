#include <cmath>
#include <iostream>

using namespace std;

// Function to calculate the factorial of a digit
int factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Function to check if a number is a curious number
bool is_curious_number(int number) {
    int sum = 0;
    int temp = number;

    while (temp > 0) {
        int digit = temp % 10;
        sum += factorial(digit);
        temp /= 10;
    }

    return sum == number;
}

int main() {
    int total_sum = 0;

    // Upper limit: 7 * 9! because 9! * 8 still has fewer digits than the number itself
    int upper_limit = 7 * factorial(9);

    for (int i = 10; i <= upper_limit; ++i) {
        if (is_curious_number(i)) {
            total_sum += i;
        }
    }

    cout << "The sum of all curious numbers is: " << total_sum << endl;

    return 0;
}
