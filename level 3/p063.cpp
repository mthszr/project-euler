#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int count = 0;

    // Only need to check n from 1 to 21, since for n > 21, no a gives an n-digit number.
    for (int n = 1; n <= 21; n++) {
        // Consider bases a from 1 to 9.
        for (int a = 1; a <= 9; a++) {
            // Calculate number of digits in a^n using the formula:
            // digits = floor(n * log10(a)) + 1.
            int digits = static_cast<int>(floor(n * log10(a))) + 1;
            if (digits == n) {
                count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}
