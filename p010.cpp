#include <iostream>
#include <vector>
using namespace std;

const int LIMIT = 2000000;

long long sum_of_primes(int limit) {
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;  // 0 and 1 are not primes
    long long sum = 0;

    for (int p = 2; p <= limit; ++p) {
        if (is_prime[p]) {
            sum += p;  // Add prime to sum
            for (int multiple = 2 * p; multiple <= limit; multiple += p) {
                is_prime[multiple] = false;  // Mark multiples as non-prime
            }
        }
    }

    return sum;
}

int main() {
    cout << "Sum of all primes below 2 million: " << sum_of_primes(LIMIT) << endl;
    return 0;
}
