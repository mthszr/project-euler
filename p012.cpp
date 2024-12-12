#include <cmath>
#include <iostream>

using namespace std;

// Function to calculate the number of divisors of a number
int count_divisors(int num) {
    int count = 0;
    int sqrt_num = sqrt(num);
    for (int i = 1; i <= sqrt_num; i++) {
        if (num % i == 0) {
            count += 2;                 // i and num / i
            if (i * i == num) count--;  // if i is the square root, count it only once
        }
    }
    return count;
}

int main() {
    int n = 1;
    int triangle_number = 0;

    while (true) {
        // Calculate the n-th triangle number
        triangle_number = n * (n + 1) / 2;

        // Count the divisors of the triangle number
        int divisors = count_divisors(triangle_number);

        // Check if the number of divisors exceeds 500
        if (divisors > 500) {
            cout << "The first triangle number with over 500 divisors is: " << triangle_number << endl;
            break;
        }
        n++;
    }

    return 0;
}
