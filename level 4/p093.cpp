#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

const double EPSILON = 1e-9;

// check if a double is nearly an integer
bool isInteger(double x) {
    return fabs(x - round(x)) < EPSILON;
}

// recursive function that computes all possible results from a list of numbers
void computeResults(const vector<double>& nums, set<double>& results) {
    int n = nums.size();
    if (n == 1) {
        results.insert(nums[0]);
        return;
    }

    // try every pair of numbers
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<double> remaining;
            // copy all numbers except indices i and j
            for (int k = 0; k < n; k++) {
                if (k != i && k != j)
                    remaining.push_back(nums[k]);
            }

            double a = nums[i], b = nums[j];
            vector<double> possibleResults;
            // addition
            possibleResults.push_back(a + b);
            // multiplication
            possibleResults.push_back(a * b);
            // subtraction in both orders
            possibleResults.push_back(a - b);
            possibleResults.push_back(b - a);
            // division if denominator is not zero
            if (fabs(b) > EPSILON)
                possibleResults.push_back(a / b);
            if (fabs(a) > EPSILON)
                possibleResults.push_back(b / a);

            // recurse with each possible result appended to remaining numbers
            for (double r : possibleResults) {
                vector<double> next = remaining;
                next.push_back(r);
                computeResults(next, results);
            }
        }
    }
}

// for a given set of four digits, return the length of consecutive positive integers starting at 1
int consecutiveLength(const vector<int>& digits) {
    vector<double> nums;
    for (int d : digits)
        nums.push_back(d);

    set<double> results;
    computeResults(nums, results);

    // collect all positive integers that are results
    set<int> positiveInts;
    for (double r : results) {
        if (r > 0 && isInteger(r))
            positiveInts.insert(static_cast<int>(round(r)));
    }

    // count consecutive integers starting at 1
    int count = 1;
    while (positiveInts.find(count) != positiveInts.end()) {
        count++;
    }
    return count - 1;
}

int main() {
    int bestLength = 0;
    vector<int> bestDigits;

    // loop over all combinations of 4 distinct digits from 1 to 9
    for (int a = 1; a <= 9; a++) {
        for (int b = a + 1; b <= 9; b++) {
            for (int c = b + 1; c <= 9; c++) {
                for (int d = c + 1; d <= 9; d++) {
                    vector<int> digits = {a, b, c, d};
                    int len = consecutiveLength(digits);
                    if (len > bestLength) {
                        bestLength = len;
                        bestDigits = digits;
                    }
                }
            }
        }
    }

    cout << "best digits: ";
    for (int d : bestDigits)
        cout << d;
    cout << "\nconsecutive run length: " << bestLength << "\n";

    return 0;
}
