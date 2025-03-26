#include <algorithm>  // For __gcd
#include <iostream>

using namespace std;

int findFractionLeftOfThreeSevenths(int max_d) {
    double target = 3.0 / 7.0;
    double closest_fraction = 0.0;
    int closest_numerator = 0;

    for (int d = 2; d <= max_d; ++d) {
        int n = (3 * d - 1) / 7;
        if (__gcd(n, d) == 1) {
            double current_fraction = static_cast<double>(n) / d;
            if (current_fraction > closest_fraction) {
                closest_fraction = current_fraction;
                closest_numerator = n;
            }
        }
    }

    return closest_numerator;
}

int main() {
    int max_d = 1000000;
    int result = findFractionLeftOfThreeSevenths(max_d);
    cout << result << endl;
    return 0;
}