#include <cmath>
#include <iostream>

using namespace std;

int main() {
    // Constants for the logarithmic approximation
    const double phi = (1 + sqrt(5)) / 2;       // Golden ratio
    const double log10_phi = log10(phi);        // log base 10 of phi
    const double log10_sqrt5 = log10(sqrt(5));  // log base 10 of sqrt(5)

    int n = 1;
    while (true) {
        // Calculate the number of digits in F_n using the logarithmic formula
        double log10_Fn = n * log10_phi - log10_sqrt5;
        int digits = floor(log10_Fn) + 1;

        if (digits >= 1000) {
            cout << "The index of the first Fibonacci number with 1000 digits is: " << n << endl;
            break;
        }

        ++n;
    }

    return 0;
}
