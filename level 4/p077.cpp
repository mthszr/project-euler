#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// function to generate all prime numbers up to a given limit using the Sieve of Eratosthenes
vector<int> generatePrimes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= limit; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p) {
                isPrime[i] = false;
            }
        }
    }
    vector<int> primes;
    for (int p = 2; p <= limit; ++p) {
        if (isPrime[p]) {
            primes.push_back(p);
        }
    }
    return primes;
}

int findFirstValueWithOver5000Ways() {
    const int targetWays = 5000;
    const int limit = 100;  // initial limit, can be increased if needed

    vector<int> primes = generatePrimes(limit);

    // dp[i] will store the number of ways to write i as a sum of primes
    vector<int> dp(limit + 1, 0);
    dp[0] = 1;  // base case

    // update the dp table for each prime
    for (int prime : primes) {
        for (int i = prime; i <= limit; ++i) {
            dp[i] += dp[i - prime];
        }
    }

    // find the first number with more than 5000 ways
    for (int i = 2; i <= limit; ++i) {
        if (dp[i] > targetWays) {
            return i;
        }
    }

    // if not found, increase the limit and try again
    return -1;  // indicates that the limit was too small
}

int main() {
    int result = findFirstValueWithOver5000Ways();
    if (result != -1) {
        cout << "the first value that can be written as the sum of primes in over 5000 ways is " << result << endl;
    } else {
        cout << "increase the limit and try again." << endl;
    }
    return 0;
}