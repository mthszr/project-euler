#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// function to count the number of unique perimeters L <= limit that form exactly one right triangle
int countUniquePerimeters(int limit) {
    // use a map to count how many times each perimeter appears
    unordered_map<int, int> perimeterCounts;

    // iterate over possible values of m to generate Pythagorean triples
    for (int m = 2; m <= sqrt(limit / 2); ++m) {
        for (int n = 1; n < m; ++n) {
            // ensure m and n are coprime and m + n is odd to generate primitive triples
            if ((m + n) % 2 == 1 && __gcd(m, n) == 1) {
                // calculate the sides of the triangle
                int a = m * m - n * n;
                int b = 2 * m * n;
                int c = m * m + n * n;
                int perimeter = a + b + c;

                // if the perimeter exceeds the limit, break out of the loop
                if (perimeter > limit) break;

                // for each multiple of the perimeter, update the count
                for (int k = 1; k * perimeter <= limit; ++k) {
                    perimeterCounts[k * perimeter]++;
                }
            }
        }
    }

    // count how many perimeters appear exactly once
    int uniqueCount = 0;
    for (const auto& pair : perimeterCounts) {
        if (pair.second == 1) {
            uniqueCount++;
        }
    }

    return uniqueCount;
}

int main() {
    int limit = 1500000;
    int result = countUniquePerimeters(limit);
    cout << result << endl;
    return 0;
}