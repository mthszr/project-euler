#include <bits/stdc++.h>
using namespace std;

// helper to check if 'x' is a perfect square
bool isPerfectSquare(long long x) {
    if (x < 0) return false;
    long long r = (long long)llround(sqrt((long double)x));
    return (r * r == x);
}

// distance from 'val' to the nearest integer
long double distToNearestInteger(long double val) {
    long double nearest = round(val);
    return fabsl(val - nearest);
}

int main() {
    // scanning a smaller range [-200000, 200000]
    // skipping perfect squares and zero
    const long long LIMIT = 200000;

    long double bestDist = 1e30L;  // large initial value
    long long bestN = 0;

    for (long long n = -LIMIT; n <= LIMIT; n++) {
        // skip zero and perfect squares
        if (n == 0) continue;
        if (n > 0 && isPerfectSquare(n)) continue;

        long double val;
        if (n > 0) {
            // cos(pi * sqrt(n))
            long double sq = sqrt((long double)n);
            val = cosl(M_PI * sq);
        } else {
            // n < 0: cos(pi * sqrt(n)) = cosh(pi * sqrt(-n))
            long double sq = sqrt((long double)(-n));
            val = coshl(M_PI * sq);
        }

        // compute distance to nearest integer
        long double d = distToNearestInteger(val);

        // update the best result if necessary
        if (d < bestDist) {
            bestDist = d;
            bestN = n;
        }
    }

    // ensure we check n = -163 explicitly (known heegner number)
    {
        long double sq = sqrt((long double)(163));
        long double val = coshl(M_PI * sq);
        long double d = distToNearestInteger(val);
        if (d < bestDist) {
            bestDist = d;
            bestN = -163;
        }
    }

    cout << "best n = " << bestN << " with distance = " << bestDist << endl;
    return 0;
}
