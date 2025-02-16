#include <cmath>
#include <iostream>

using namespace std;

// check if a number is pentagonal
// a number x is pentagonal if (sqrt(24*x + 1) + 1) / 6 is an integer
bool isPentagonal(long long x) {
    double d = sqrt(24 * x + 1);
    double n = (d + 1.0) / 6.0;
    return n == floor(n);
}

int main() {
    // since 40755 is h143, we start with the next hexagonal number
    long long i = 144;

    while (true) {
        // every hexagonal number is triangular
        // h_i = i * (2*i - 1)
        long long hexNum = i * (2 * i - 1);

        // check if it's also pentagonal
        if (isPentagonal(hexNum)) {
            cout << "the next triangle, pentagonal, and hexagonal number is: "
                 << hexNum << endl;
            break;
        }

        i++;
    }

    return 0;
}
