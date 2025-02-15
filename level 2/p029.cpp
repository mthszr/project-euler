#include <cmath>
#include <iostream>
#include <set>

using namespace std;

int main() {
    set<double> distinctTerms;  // Set to store distinct powers

    // Loop over all integer values of a and b
    for (int a = 2; a <= 100; ++a) {
        for (int b = 2; b <= 100; ++b) {
            // Compute a^b and insert it into the set
            double power = pow(a, b);
            distinctTerms.insert(power);
        }
    }

    // Output the number of distinct terms
    cout << "Number of distinct terms: " << distinctTerms.size() << endl;

    return 0;
}
