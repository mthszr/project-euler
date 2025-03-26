#include <cmath>
#include <iostream>
using namespace std;

int main() {
    // count the number of continued fractions for sqrt(n) with odd period for n <= 10000
    int odd_period_count = 0;

    // loop over n from 2 to 10000
    for (int n = 2; n <= 10000; n++) {
        // check if n is a perfect square
        int int_sqrt = static_cast<int>(sqrt(n));
        if (int_sqrt * int_sqrt == n) {
            // skip perfect squares as their continued fraction terminates
            continue;
        }

        // initialize values for the algorithm
        int m = 0;
        int d = 1;
        int a0 = int_sqrt;
        int a = a0;
        int period = 0;

        // compute the continued fraction period
        do {
            // update m, d, and a according to the algorithm
            m = d * a - m;
            d = (n - m * m) / d;
            a = (a0 + m) / d;
            period++;
        } while (a != 2 * a0);

        // if the period is odd, increment the count
        if (period % 2 == 1) {
            odd_period_count++;
        }
    }

    // output the result
    cout << odd_period_count << endl;

    return 0;
}
