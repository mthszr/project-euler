#include <cmath>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

// returns a list of primes up to n using a simple sieve of eratosthenes
vector<int> sieve(int n) {
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            // mark multiples of i as not prime
            for (long long j = (long long)i * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    return primes;
}

int main() {
    const int limit = 50000000;
    int sqrtLimit = static_cast<int>(sqrt(limit));

    // get primes up to sqrt(limit)
    vector<int> primes = sieve(sqrtLimit);

    vector<int> squares;
    vector<int> cubes;
    vector<int> fourthPowers;  // tesseracts

    // compute prime squares that are less than limit
    for (int p : primes) {
        long long sq = (long long)p * p;
        if (sq < limit)
            squares.push_back(sq);
        else
            break;  // since primes are in increasing order
    }

    // compute prime cubes that are less than limit
    for (int p : primes) {
        long long cube = (long long)p * p * p;
        if (cube < limit)
            cubes.push_back(cube);
        else
            break;
    }

    // compute prime fourth powers that are less than limit
    for (int p : primes) {
        long long fourth = (long long)p * p * p * p;
        if (fourth < limit)
            fourthPowers.push_back(fourth);
        else
            break;
    }

    // use an unordered_set to avoid duplicate sums
    unordered_set<int> sums;

    // iterate over all combinations of square, cube, and fourth power
    for (int s : squares) {
        for (int c : cubes) {
            for (int t : fourthPowers) {
                int sum = s + c + t;
                if (sum < limit)
                    sums.insert(sum);
            }
        }
    }

    cout << sums.size() << endl;
    return 0;
}
