#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    // create a map to group cubes by their sorted digit strings
    unordered_map<string, vector<long long>> cubeGroups;
    // set an upper limit for n (n^3); 10000 is a reasonable limit for this problem
    long long limit = 10000;

    // iterate over n from 1 to limit - 1
    for (long long n = 1; n < limit; n++) {
        long long cube = n * n * n;
        // convert the cube to a string
        string cubeStr = to_string(cube);
        // sort the digits of the cube string
        sort(cubeStr.begin(), cubeStr.end());
        // group the cube under the sorted digit string key
        cubeGroups[cubeStr].push_back(cube);
    }

    // initialize the answer with the maximum possible long long value
    long long minCube = numeric_limits<long long>::max();
    // iterate through the groups to find one with exactly five cube permutations
    for (auto &pair : cubeGroups) {
        if (pair.second.size() == 5) {
            // find the smallest cube in this group
            long long smallestInGroup = *min_element(pair.second.begin(), pair.second.end());
            if (smallestInGroup < minCube) {
                minCube = smallestInGroup;
            }
        }
    }

    cout << "smallest cube with exactly five cube permutations: " << minCube << endl;
    return 0;
}
