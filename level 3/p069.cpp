#include <iostream>
using namespace std;

// check if a number is prime
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    const int limit = 1000000;
    long long n = 1;
    int p = 2;
    // multiply by primes while product does not exceed the limit
    while (n * p <= limit) {
        if (is_prime(p)) {
            n *= p;
        }
        p++;
    }
    cout << n << endl;
    return 0;
}
