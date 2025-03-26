#include <cmath>
#include <iostream>
using namespace std;

// fast exponentiation under modulo
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

// check if polynomial has a root modulo p
bool has_root(int p) {
    for (int x = 0; x < p; x++) {
        if ((x * x * x - 3 * x + 4) % p == 0)
            return true;
    }
    return false;
}

int main() {
    int start = 1000000000;
    int end = 1100000000;
    long long total = 0;

    // iterate through primes
    for (int p = start; p <= end; p++) {
        if (p < 2) continue;
        bool is_prime = true;
        for (int i = 2; i <= sqrt(p); i++) {
            if (p % i == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            if (has_root(p)) {
                total += 0;
            } else {
                // Placeholder for actual product calculation
                total += 1;
            }
        }
    }

    cout << total << endl;
    return 0;
}