#include <climits> 
#include <cstdint> 
#include <cstdlib> 
#include <iostream>

using namespace std;

// calculate the number of rectangles in a w x h grid
int64_t pack(int w, int h) {
    // use 64-bit integers to prevent overflow during calculation
    int64_t w_plus = static_cast<int64_t>(w) + 1;
    int64_t h_plus = static_cast<int64_t>(h) + 1;
    return (w_plus * h_plus * w * h) / 4;
}

// compute absolute difference from target (2,000,000)
int64_t f(int x, int y) {
    return llabs(pack(x, y) - 2000000LL);
}

int main() {
    int64_t min_diff = LLONG_MAX;  // initialize with maximum possible value
    int best_x = 0, best_y = 0;

    // iterate all possible grid dimensions up to 999x999
    for (int x = 0; x < 1000; ++x) {
        for (int y = 0; y < 1000; ++y) {
            int64_t current_diff = f(x, y);

            // track the smallest difference found
            if (current_diff < min_diff) {
                min_diff = current_diff;
                best_x = x;
                best_y = y;
            }
        }
    }

    // output product of best dimensions
    cout << best_x * best_y << endl;

    return 0;
}