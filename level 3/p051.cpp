#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// function to check if a number is prime
bool is_prime(long long n) {
    // numbers less than 2 are not prime
    if (n < 2)
        return false;
    // 2 is prime, and even numbers >2 are not prime
    if (n % 2 == 0)
        return n == 2;
    // check odd divisors up to sqrt(n)
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// main function
int main() {
    // we start checking from 11 because small primes have too few digits to form a family
    long long candidate = 11;
    while (true) {
        // if candidate is not prime, move to next number
        if (!is_prime(candidate)) {
            candidate++;
            continue;
        }
        // convert candidate to string for digit manipulation
        string s = to_string(candidate);
        int len = s.size();
        bool found_family = false;

        // try each digit from '0' to '9' as the candidate digit for replacement
        for (char digit = '0'; digit <= '9'; digit++) {
            // vector to store positions where the digit appears in the candidate
            vector<int> positions;
            for (int i = 0; i < len; i++) {
                if (s[i] == digit)
                    positions.push_back(i);
            }
            // if the digit does not occur, skip
            if (positions.empty())
                continue;

            // iterate over all non-empty subsets of positions
            // using bitmasking on the positions vector
            int m = positions.size();
            // from 1 to (2^m)-1 to consider every non-empty combination
            for (int mask = 1; mask < (1 << m); mask++) {
                int prime_count = 0;
                // for each replacement digit from '0' to '9'
                for (char rep = '0'; rep <= '9'; rep++) {
                    string candidate_str = s;
                    bool skip = false;

                    // replace all positions indicated by the current mask with the replacement digit
                    for (int j = 0; j < m; j++) {
                        if (mask & (1 << j)) {
                            int pos = positions[j];
                            // if the leftmost digit is replaced by '0', skip to avoid leading zero
                            if (pos == 0 && rep == '0') {
                                skip = true;
                                break;
                            }
                            candidate_str[pos] = rep;
                        }
                    }
                    if (skip)
                        continue;

                    long long num = stoll(candidate_str);
                    // count the candidate only if it is prime
                    if (is_prime(num))
                        prime_count++;
                }
                // if we found a family with exactly eight prime values, output the candidate and exit
                if (prime_count == 8) {
                    cout << candidate << endl;
                    return 0;
                }
            }
        }
        // move to the next candidate number
        candidate++;
    }

    return 0;
}
