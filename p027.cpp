#include <cmath>
#include <iostream>
using namespace std;

// Function to check if a number is prime
bool is_prime(int n) {
    if (n < 2) return false;                   // Numbers less than 2 are not prime
    for (int i = 2; i <= sqrt(abs(n)); i++) {  // Check divisors from 2 to sqrt(n)
        if (n % i == 0) return false;          // Not prime if divisible
    }
    return true;  // Prime number
}

// Function to count consecutive primes produced by the quadratic formula
int count_consecutive_primes(int a, int b) {
    int n = 0;
    while (is_prime(n * n + a * n + b)) {  // Check if the result is prime
        n++;
    }
    return n;  // Return count of consecutive primes
}

int main() {
    int best_a = 0;      // Coefficient 'a' with maximum primes
    int best_b = 0;      // Coefficient 'b' with maximum primes
    int max_primes = 0;  // Maximum count of consecutive primes

    // Iterate through all possible values of 'a' and 'b'
    for (int a = -999; a < 1000; a++) {
        for (int b = -1000; b <= 1000; b++) {
            if (is_prime(b)) {                                // 'b' must be prime for n = 0
                int primes = count_consecutive_primes(a, b);  // Count consecutive primes
                if (primes > max_primes) {
                    max_primes = primes;
                    best_a = a;
                    best_b = b;
                }
            }
        }
    }

    // Output the question as the result
    cout << "What is the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0?" << endl;

    return 0;
}
