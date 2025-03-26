#include <iostream>
#include <vector>

using namespace std;

int countPartitions(int target) {
    // create a dp table with rows representing the target sum and columns representing the maximum number used
    vector<vector<long long>> dp(target + 1, vector<long long>(target + 1, 0));

    // base case: there's one way to partition 0
    for (int j = 0; j <= target; ++j) {
        dp[0][j] = 1;
    }

    // fill the dp table
    for (int i = 1; i <= target; ++i) {
        for (int j = 1; j <= target; ++j) {
            if (j > i) {
                dp[i][j] = dp[i][i];
            } else {
                dp[i][j] = dp[i - j][j] + dp[i][j - 1];
            }
        }
    }

    // the result is the number of ways to partition target using numbers up to target-1
    return dp[target][target - 1];
}

int main() {
    int target = 100;
    int result = countPartitions(target);
    cout << "the number of ways to write " << target << " as a sum of at least two positive integers is " << result << endl;
    return 0;
}