#include <cmath>
#include <iostream>

using namespace std;

// function to check if a number is prime
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int side_length = 1;  // start with 1x1 spiral
    int prime_count = 0;
    int total_diagonals = 1;  // start with the center 1

    for (int n = 3;; n += 2) {  // increment side length by 2
        int bottom_right = n * n;
        int bottom_left = bottom_right - (n - 1);
        int top_left = bottom_left - (n - 1);
        int top_right = top_left - (n - 1);

        // count primes
        if (is_prime(bottom_left)) prime_count++;
        if (is_prime(top_left)) prime_count++;
        if (is_prime(top_right)) prime_count++;

        total_diagonals += 4;  // each layer adds 4 diagonal numbers
        side_length = n;       // update side length

        // check the prime ratio
        if ((100.0 * prime_count / total_diagonals) < 10.0) break;
    }

    cout << side_length << endl;
    return 0;
}
