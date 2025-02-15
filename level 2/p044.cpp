#include <cmath>
#include <iostream>
using namespace std;

// checks if a given number x is pentagonal
bool isPentagonal(long long x) {
    // a number x is pentagonal if n = (sqrt(24*x + 1) + 1)/6 is an integer
    long double n = (sqrt(24 * x + 1) + 1) / 6;
    return n == floor(n);
}

// returns the nth pentagonal number using the formula P(n) = n*(3*n-1)/2
long long pentagonal(int n) {
    return (long long)n * (3LL * n - 1) / 2;
}

int main() {
    long long minD = -1;  // will hold the minimal difference found
    int limit = 10000;    // upper bound for the index (adjust as needed)

    // iterate over pairs of pentagonal numbers
    for (int j = 1; j < limit; j++) {
        long long Pj = pentagonal(j);
        for (int k = j + 1; k < limit; k++) {
            long long Pk = pentagonal(k);
            long long sum = Pj + Pk;
            long long diff = Pk - Pj;

            // check if both the sum and difference are pentagonal
            if (isPentagonal(sum) && isPentagonal(diff)) {
                if (minD < 0 || diff < minD) {
                    minD = diff;
                    cout << "found pair: P(" << j << ") = " << Pj
                         << ", P(" << k << ") = " << Pk
                         << ", diff = " << diff << endl;
                }
            }
        }
    }

    cout << "minimum difference d = " << minD << endl;
    return 0;
}
