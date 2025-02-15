#include <iostream> 
using namespace std;

long largest_prime_factor(long n) {
    long factor = 2;
    long largest_factor = 1;

    while (factor * factor <= n) {
        while (n % factor == 0) {
            largest_factor = factor;  // Update the largest factor
            n /= factor;              // Reduce n by dividing by the factor
        }
        factor++;
    }

    if (n > 1) {
        largest_factor = n;  // If a number greater than 1 remains, it's the largest prime factor
    }

    return largest_factor;
}

int main() {
    long number = 600851475143;
    cout << "The largest prime factor of " << number << " is " << largest_prime_factor(number) << endl;
    return 0;
}