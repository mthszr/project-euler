#include <iostream>
#include <unordered_map>

using namespace std;

// Function to compute the length of the collatz sequence
long long collatz_sequence_length(long long n, unordered_map<long long, long long>& memo) {
    if (n == 1) return 1;

    // Check if the result is already computed
    if (memo.count(n)) return memo[n];

    long long next;
    if (n % 2 == 0) {
        next = n / 2;
    } else {
        next = 3 * n + 1;
    }

    // Memoize the result
    memo[n] = 1 + collatz_sequence_length(next, memo);
    return memo[n];
}

int main() {
    const long long limit = 1000000;
    long long max_length = 0;
    long long starting_number = 0;

    // Memoization map
    unordered_map<long long, long long> memo;

    for (long long i = 1; i < limit; ++i) {
        long long length = collatz_sequence_length(i, memo);

        // Check if this chain is the longest
        if (length > max_length) {
            max_length = length;
            starting_number = i;
        }
    }

    cout << "The starting number under " << limit
         << " that produces the longest chain is: " << starting_number << endl;
    cout << "The chain length is: " << max_length << endl;

    return 0;
}
