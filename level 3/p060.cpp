#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// mod multiplication under mod (to avoid overflow)
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull mod) {
    ull result = 0;
    a %= mod;
    while (b) {
        if (b & 1)
            result = (result + a) % mod;
        a = (a << 1) % mod;
        b >>= 1;
    }
    return result;
}

// mod exponentiation using modmul
ull modexp(ull base, ull exp, ull mod) {
    ull result = 1;
    base %= mod;
    while (exp) {
        if (exp & 1)
            result = modmul(result, base, mod);
        base = modmul(base, base, mod);
        exp >>= 1;
    }
    return result;
}

// miller-rabin primality test for 64-bit numbers
bool isPrime(ull n) {
    if (n < 2)
        return false;
    // check small primes
    int smallPrimes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; i++) {
        if (n == smallPrimes[i])
            return true;
        if (n % smallPrimes[i] == 0)
            return false;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1ULL) == 0) {
        d /= 2;
        s++;
    }
    // set of witnesses sufficient for 64-bit numbers
    ull witnesses[7] = {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL};
    for (int i = 0; i < 7; i++) {
        ull a = witnesses[i] % n;
        if (a == 0)
            continue;
        ull x = modexp(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = modmul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite)
            return false;
    }
    return true;
}

// function to compute concatenation of two numbers: a concatenated with b
long long concat(int a, int b) {
    int temp = b;
    long long power = 1;
    while (temp > 0) {
        power *= 10;
        temp /= 10;
    }
    return (long long)a * power + b;
}

// check if concatenating a and b in both orders gives primes
bool isConcatPrime(int a, int b) {
    long long ab = concat(a, b);
    long long ba = concat(b, a);
    return isPrime(ab) && isPrime(ba);
}

// global vector to store primes for search
vector<int> primesList;

// simple sieve to generate primes up to n
void sieve(int n) {
    vector<bool> isPrimeArr(n + 1, true);
    isPrimeArr[0] = isPrimeArr[1] = false;
    for (int i = 2; i * i <= n; i++) {
        if (isPrimeArr[i]) {
            for (int j = i * i; j <= n; j += i)
                isPrimeArr[j] = false;
        }
    }
    for (int i = 2; i <= n; i++) {
        if (isPrimeArr[i])
            primesList.push_back(i);
    }
}

int bestSum = 1e9;  // initialize with a large number
vector<int> bestSet;

// recursive search for sets of primes with the concatenation property
void search(vector<int>& currentSet, int start, int currentSum) {
    if (currentSet.size() == 5) {
        if (currentSum < bestSum) {
            bestSum = currentSum;
        }
        return;
    }
    for (int i = start; i < primesList.size(); i++) {
        int p = primesList[i];
        // prune: if current sum plus p for each remaining prime exceeds bestSum, break
        if (currentSum + p * (5 - currentSet.size()) >= bestSum)
            break;
        bool valid = true;
        // check current candidate with each prime in the current set
        for (int q : currentSet) {
            if (!isConcatPrime(q, p)) {
                valid = false;
                break;
            }
        }
        if (valid) {
            currentSet.push_back(p);
            search(currentSet, i + 1, currentSum + p);
            currentSet.pop_back();
        }
    }
}

int main() {
    // generate primes up to 10000
    sieve(10000);

    vector<int> currentSet;
    search(currentSet, 0, 0);

    cout << bestSum << endl;
    return 0;
}
