#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

set<string> solutions;
int n, targetSum;

void backtrack(int pos, vector<int>& inner, vector<int>& outer, int used) {
    if (pos == n - 1) {
        int lastOuter = targetSum - (inner[n - 1] + inner[0]);
        if (lastOuter < 1 || lastOuter > 2 * n) return;
        if (used & (1 << lastOuter)) return;
        outer[n - 1] = lastOuter;
        // ensure the starting group (with the smallest outer node) is first.
        for (int i = 1; i < n; i++)
            if (outer[i] < outer[0])
                return;
        stringstream ss;
        // concatenate each triplet: outer, inner, inner(next)
        for (int i = 0; i < n; i++)
            ss << outer[i] << inner[i] << inner[(i + 1) % n];
        solutions.insert(ss.str());
        return;
    }
    for (int candidate = 1; candidate <= 2 * n; candidate++) {
        if (used & (1 << candidate))
            continue;
        inner[pos + 1] = candidate;
        int newUsed = used | (1 << candidate);
        int outerVal = targetSum - (inner[pos] + candidate);
        if (outerVal < 1 || outerVal > 2 * n)
            continue;
        if (newUsed & (1 << outerVal))
            continue;
        newUsed |= (1 << outerVal);
        outer[pos] = outerVal;
        backtrack(pos + 1, inner, outer, newUsed);
    }
}

int main() {
    n = 5;  // we use numbers 1..10 for a 5-gon ring.
    // for a 5-gon ring that uses the numbers 1..10 with 10 on the outer ring,
    // the magic sum (targetsum) is known to be between 14 and 18.
    for (targetSum = 14; targetSum <= 18; targetSum++) {
        vector<int> inner(n, 0), outer(n, 0);
        int used = 0;
        for (int candidate = 1; candidate <= 2 * n; candidate++) {
            inner[0] = candidate;
            int newUsed = used | (1 << candidate);
            backtrack(0, inner, outer, newUsed);
        }
    }
    string maxSolution = "";
    // only consider solutions that yield a 16-digit string.
    for (const string& sol : solutions)
        if (sol.size() == 16 && sol > maxSolution)
            maxSolution = sol;
    cout << maxSolution;
    return 0;
}
