#include <cmath>
#include <iostream>
using namespace std;

// Function to check if a number is prime
bool is_prime(int n) {
    if (n <= 1) return false;      // 0 and 1 are not prime numbers
    if (n == 2) return true;       // 2 is the only even prime number
    if (n % 2 == 0) return false;  // Other even numbers are not prime

    // Check for factors from 3 to sqrt(n), skipping even numbers
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int count = 0;   // Count of prime numbers found
    int number = 1;  // Starting from the number 1

    // Loop until the 10001st prime is found
    while (count < 10001) {
        number++;  // Check the next number
        if (is_prime(number)) {
            count++;  // Increment the count if the number is prime
        }
    }

    // Output the 10001st prime number
    cout << "The 10001st prime number is: " << number << endl;

    return 0;
}
