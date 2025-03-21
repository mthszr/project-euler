#include <iostream>
using namespace std;

// computes the number of divisors of n^2 given n
int divisorCountOfNSquared(int n) {
    int temp = n;
    int countDiv = 1;
    // iterate over possible prime factors
    for (int p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            int exp = 0;
            // count the exponent of the prime factor p in n
            while (temp % p == 0) {
                exp++;
                temp /= p;
            }
            // for n^2, the exponent becomes 2*exp, so the number of divisors contributed is (2*exp + 1)
            countDiv *= (2 * exp + 1);
        }
    }
    // if there is any prime factor left
    if (temp > 1) {
        countDiv *= (2 * 1 + 1);
    }
    return countDiv;
}

int main() {
    int threshold = 1000;  // we need more than 1000 solutions
    int n = 1;

    while (true) {
        int d = divisorCountOfNSquared(n);
        // number of distinct solutions = (d + 1) / 2
        if ((d + 1) / 2 > threshold) {
            cout << n << endl;
            break;
        }
        n++;
    }

    return 0;
}
