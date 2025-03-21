#include <iostream>
using namespace std;

int main() {
    // count of binomial coefficients greater than one-million
    int count = 0;

    // loop over n from 1 to 100
    for (int n = 1; n <= 100; n++) {
        // c represents the binomial coefficient (n choose r)
        // initialize with (n choose 0) = 1
        long double c = 1.0L;

        // loop over r from 0 to n
        for (int r = 0; r <= n; r++) {
            // if the current binomial coefficient is greater than one-million,
            // increase our count
            if (c > 1000000.0L)
                count++;

            // update c to be (n choose (r+1)) using the relation:
            // (n choose (r+1)) = (n choose r) * (n - r) / (r + 1)
            if (r < n)
                c = c * (n - r) / (r + 1);
        }
    }

    // output the total count of binomial coefficients exceeding one-million
    cout << count << endl;

    return 0;
}

