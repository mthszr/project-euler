#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    const int limit = 1000000;
    // precompute sum of proper divisors for numbers from 1 to limit
    vector<int> sumDiv(limit + 1, 1);
    sumDiv[0] = 0;  // not used
    sumDiv[1] = 0;  // proper divisors of 1 sum to 0
    for (int i = 2; i * 2 <= limit; i++) {
        for (int j = 2 * i; j <= limit; j += i) {
            sumDiv[j] += i;
        }
    }

    int bestLength = 0;
    int bestMinMember = 0;
    // track numbers already processed to avoid duplicate work
    vector<bool> processed(limit + 1, false);

    // loop over possible starting numbers
    for (int start = 2; start <= limit; start++) {
        if (processed[start])
            continue;

        // use a map to record the index at which each number appears in the chain
        unordered_map<int, int> chainIndex;
        vector<int> chain;
        int current = start;
        bool validChain = true;

        while (true) {
            // if current is out of range, break; chain is invalid
            if (current < 1 || current > limit) {
                validChain = false;
                break;
            }
            // if current is already in the chain, a cycle is found
            if (chainIndex.find(current) != chainIndex.end()) {
                int cycleStart = chainIndex[current];
                // extract the cycle from the chain
                vector<int> cycle(chain.begin() + cycleStart, chain.end());
                // check that all cycle members are within range
                bool allInRange = true;
                for (int num : cycle) {
                    if (num < 1 || num > limit) {
                        allInRange = false;
                        break;
                    }
                }
                if (!allInRange) {
                    validChain = false;
                    break;
                }
                int cycleLength = cycle.size();
                int cycleMin = *min_element(cycle.begin(), cycle.end());
                if (cycleLength > bestLength) {
                    bestLength = cycleLength;
                    bestMinMember = cycleMin;
                } else if (cycleLength == bestLength && cycleMin < bestMinMember) {
                    bestMinMember = cycleMin;
                }
                break;
            }
            // record current number and its index in the chain
            chainIndex[current] = chain.size();
            chain.push_back(current);
            // move to next number in the chain
            current = sumDiv[current];
        }

        // mark all numbers in this chain as processed
        for (int num : chain) {
            if (num >= 1 && num <= limit)
                processed[num] = true;
        }
    }

    cout << bestMinMember << endl;
    return 0;
}
