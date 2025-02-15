#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    // map to store the count of solutions for each perimeter p
    unordered_map<int, int> solutioncounts;

    // iterate through all possible perimeters p < 1000
    for (int p = 1; p < 1000; ++p) {
        // iterate through possible values of a
        for (int a = 1; a < p / 2; ++a) {
            // iterate through possible values of b
            for (int b = a; b < p / 2; ++b) {
                // compute c
                int c = p - a - b;
                // check if the triplet forms a valid right-angle triangle
                if (c > 0 && a * a + b * b == c * c) {
                    // increment the solution count for this perimeter
                    solutioncounts[p]++;
                }
            }
        }
    }

    // find the perimeter with the maximum number of solutions
    int maxp = 0;
    int maxsolutions = 0;
    for (const auto& entry : solutioncounts) {
        if (entry.second > maxsolutions) {
            maxsolutions = entry.second;
            maxp = entry.first;
        }
    }

    // output the result
    cout << maxp << endl;

    return 0;
}