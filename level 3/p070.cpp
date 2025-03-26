#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

// Check if two integers are permutations of each other.
bool isPermutation(int a, int b) {
    string s1 = to_string(a);
    string s2 = to_string(b);
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());
    return s1 == s2;
}

// Sieve of Eratosthenes to generate primes up to n.
vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i])
            primes.push_back(i);
    }
    return primes;
}

int main() {
    const int limit = 10000000;
    // We only need primes up to a certain limit; here, using 10000 is safe
    // because if n = p * q < 10^7 then both p and q are less than 10^4.
    vector<int> primes = sieve(10000);

    double minRatio = numeric_limits<double>::max();
    int bestN = 0;
    int size = primes.size();

    // Iterate over pairs of primes.
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            long long n = (long long)primes[i] * primes[j];
            if (n >= limit)
                break;
            // Euler's totient function for n = p * q is: (p - 1)*(q - 1)
            int phi = (primes[i] - 1) * (primes[j] - 1);
            if (isPermutation(n, phi)) {
                double ratio = (double)n / phi;
                if (ratio < minRatio) {
                    minRatio = ratio;
                    bestN = n;
                }
            }
        }
    }

    cout << bestN << endl;
    return 0;
}
