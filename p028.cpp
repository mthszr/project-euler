#include <iostream>
using namespace std;

int main() {
    int n = 1001;       // Size of the spiral
    long long sum = 1;  // Start with the center value which is 1

    for (int layer = 1; layer <= (n - 1) / 2; layer++) {
        // The numbers on the diagonals for the current layer
        // Top-right corner, Top-left corner, Bottom-left corner, Bottom-right corner
        sum += 4 * (layer * layer) + 10 * layer;
    }

    cout << "The sum of the numbers on the diagonals in a " << n << " by " << n << " spiral is: " << sum << endl;

    return 0;
}
