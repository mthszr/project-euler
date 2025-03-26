#include <algorithm>  // For __gcd
#include <iostream>
using namespace std;

int countFractionsInRange(int max_d) {
    int count = 0;

    for (int d = 2; d <= max_d; ++d) {
        int lower_n = d / 3 + 1;    // Smallest n such that n/d > 1/3
        int upper_n = (d - 1) / 2;  // Largest n such that n/d < 1/2

        for (int n = lower_n; n <= upper_n; ++n) {
            if (__gcd(n, d) == 1) {
                ++count;
            }
        }
    }

    return count;
}

int main() {
    int max_d = 12000;
    int result = countFractionsInRange(max_d);
    cout << result << endl;
    return 0;
}