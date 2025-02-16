#include <iostream>

using namespace std;

// function to count the distinct prime factors of a number
int count_distinct_prime_factors(int n) {
    int count = 0;
    int factor = 2;
    // loop until n is reduced to 1
    while (n > 1 && factor * factor <= n) {
        // if factor divides n, then it's a prime factor
        if (n % factor == 0) {
            count++;
            // divide out all occurrences of the factor
            while (n % factor == 0) {
                n /= factor;
            }
        }
        factor++;
    }
    // if n is greater than 1, then it is a prime factor itself
    if (n > 1) {
        count++;
    }
    return count;
}

int main() {
    // start checking from 2 upwards
    int n = 2;

    while (true) {
        // check if n, n+1, n+2, and n+3 each have 4 distinct prime factors
        if (count_distinct_prime_factors(n) == 4 &&
            count_distinct_prime_factors(n + 1) == 4 &&
            count_distinct_prime_factors(n + 2) == 4 &&
            count_distinct_prime_factors(n + 3) == 4) {
            cout << n << endl;
            break;
        }
        n++;
    }

    return 0;
}
