#include <iostream>
#include <vector>
using namespace std;

int main() {
    // set the limit to one million
    const int limit = 1000000;

    // create a sieve to determine primes up to limit
    vector<bool> is_prime(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= limit; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                is_prime[j] = false;
            }
        }
    }

    // store all primes below limit in a vector
    vector<int> primes;
    for (int i = 2; i < limit; i++) {
        if (is_prime[i])
            primes.push_back(i);
    }

    // build a prefix sum array for the primes to enable fast consecutive sum calculation
    vector<long long> prefix(primes.size() + 1, 0);
    for (size_t i = 0; i < primes.size(); i++) {
        prefix[i + 1] = prefix[i] + primes[i];
    }

    int max_length = 0;
    int result = 0;
    int n = primes.size();

    // iterate over each starting index for the consecutive sum
    for (int i = 0; i < n; i++) {
        // try sequences longer than the current max_length
        for (int j = i + max_length; j < n; j++) {
            long long sum = prefix[j + 1] - prefix[i];
            if (sum >= limit)
                break;  // if the sum exceeds the limit, no need to check further in this sequence

            // if the sum is prime and the sequence length is longer than max_length, update the result
            if (is_prime[sum]) {
                int length = j - i + 1;
                if (length > max_length) {
                    max_length = length;
                    result = sum;
                }
            }
        }
    }

    cout << result << endl;
    return 0;
}