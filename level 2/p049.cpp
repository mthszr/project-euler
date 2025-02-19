#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// generate a sieve of primes up to n (inclusive)
vector<bool> generate_sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

// return a sorted string of the digits of n
string sorted_digits(int n) {
    string s = to_string(n);
    sort(s.begin(), s.end());
    return s;
}

int main() {
    // generate sieve for numbers up to 9999
    vector<bool> is_prime = generate_sieve(9999);

    // iterate over 4-digit primes
    for (int p = 1000; p <= 9999; p++) {
        if (!is_prime[p])
            continue;

        // try different differences
        for (int d = 1; p + 2 * d <= 9999; d++) {
            int q = p + d;
            int r = p + 2 * d;

            // check if q and r are primes
            if (!is_prime[q] || !is_prime[r])
                continue;

            // check if p, q, r are permutations of each other
            if (sorted_digits(p) == sorted_digits(q) &&
                sorted_digits(p) == sorted_digits(r)) {
                // exclude the given sequence 1487, 4817, 8147
                if (p == 1487)
                    continue;

                // form the concatenated 12-digit number
                string result = to_string(p) + to_string(q) + to_string(r);
                cout << result << endl;
                return 0;
            }
        }
    }

    return 0;
}
