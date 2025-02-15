#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function to generate the sieve of eratosthenes up to limit
vector<bool> generateSieve(int limit) {
    vector<bool> isPrime(limit, true);
    if (limit > 0) isPrime[0] = false;
    if (limit > 1) isPrime[1] = false;

    for (int i = 2; i * i < limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j < limit; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return isPrime;
}

// function that checks if a prime number is circular.
// it converts the number to a string and rotates the digits.
bool isCircularPrime(int num, const vector<bool>& isPrime) {
    string s = to_string(num);
    int len = s.size();

    // check every rotation
    for (int i = 0; i < len; i++) {
        // create a rotation by splitting the string and concatenating in swapped order.
        string rotated = s.substr(i) + s.substr(0, i);
        int rotatedNum = stoi(rotated);

        // check if the rotated number is prime.
        // (rotatednum is always less than the limit because we are below one million)
        if (!isPrime[rotatedNum]) {
            return false;
        }
    }
    return true;
}

int main() {
    const int LIMIT = 1000000;
    // generate a sieve of primes up to limit
    vector<bool> isPrime = generateSieve(LIMIT);

    int countCircularPrimes = 0;

    // iterate over all numbers below limit.
    for (int i = 2; i < LIMIT; i++) {
        if (isPrime[i] && isCircularPrime(i, isPrime)) {
            countCircularPrimes++;
        }
    }

    cout << "Number of circular primes below one million: "
         << countCircularPrimes << endl;

    return 0;
}
