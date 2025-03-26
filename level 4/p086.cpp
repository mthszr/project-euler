#include <cmath>
#include <iostream>

using namespace std;

// checks if x is a perfect square
bool isSquare(long long x) {
    long long r = static_cast<long long>(sqrt(x));
    return r * r == x;
}

// for a given m, counts the number of pairs (a, b) with 1 ≤ a ≤ m, a ≤ b ≤ m
// such that (a + b)² + m² is a perfect square
int solutions(int m) {
    int count = 0;
    for (int a = 1; a <= m; ++a) {
        for (int b = a; b <= m; ++b) {
            long long sum = a + b;
            long long expression = sum * sum + static_cast<long long>(m) * m;
            if (isSquare(expression))
                ++count;
        }
    }
    return count;
}

int main() {
    long long cumulative = 0;
    int termCount = 0;
    int m = 0;

    // continue while the cumulative sum of solutions(m) is at most 1,000,000
    while (true) {
        int sol = solutions(m);
        cumulative += sol;
        if (cumulative > 1000000)
            break;
        termCount++;
        m++;
    }

    cout << termCount << endl;
    return 0;
}
