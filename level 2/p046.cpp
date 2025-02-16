#include <cmath>
#include <iostream>

using namespace std;

// check if a number is prime
bool is_prime(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main() {
    // iterate over odd numbers starting from 9
    // since even numbers and primes are not considered
    for (int n = 9;; n += 2) {
        // skip if n is prime (we need odd composite numbers)
        if (is_prime(n))
            continue;

        bool can_be_written = false;
        // try to write n as (prime + 2 * square)
        for (int p = 2; p < n; p++) {
            if (!is_prime(p))
                continue;
            int remainder = n - p;
            // check if remainder is twice a square
            if (remainder % 2 == 0) {
                int half = remainder / 2;
                int k = static_cast<int>(sqrt(half));
                if (k * k == half) {
                    can_be_written = true;
                    break;
                }
            }
        }

        // if n cannot be written in the desired form, print and exit
        if (!can_be_written) {
            cout << n << endl;
            break;
        }
    }

    return 0;
}
