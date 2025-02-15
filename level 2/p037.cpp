#include <cmath>
#include <iostream>
#include <string>

    using namespace std;

// function to check if a number is prime
bool isPrime(int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    if (n % 2 == 0)
        return false;
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// function to check if a prime is truncatable from left to right and right to left
bool isTruncatable(int n) {
    string s = to_string(n);

    // check truncation from left to right
    for (size_t i = 1; i < s.size(); i++) {
        int truncated = stoi(s.substr(i));
        if (!isPrime(truncated))
            return false;
    }

    // check truncation from right to left
    for (size_t i = s.size() - 1; i > 0; i--) {
        int truncated = stoi(s.substr(0, i));
        if (!isPrime(truncated))
            return false;
    }

    return true;
}

int main() {
    int count = 0;
    long long sum = 0;
    int n = 11;  // start with 11 since single-digit primes are not considered truncatable

    // loop until we find the 11 truncatable primes
    while (count < 11) {
        if (isPrime(n) && isTruncatable(n)) {
            sum += n;
            count++;
        }
        n++;
    }

    cout << sum << endl;
    return 0;
}