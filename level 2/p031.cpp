#include <iostream>
#include <vector>
using namespace std;

// Function to calculate the number of ways to make £2 using coins
int ways_to_make_200() {
    const int target = 200;                               // Target amount in pence
    vector<int> coins = {1, 2, 5, 10, 20, 50, 100, 200};  // Available coins
    vector<int> dp(target + 1, 0);                        // dp[i] represents the number of ways to make i pence

    dp[0] = 1;  // There's one way to make 0p, by using no coins

    // Update the dp array for each coin
    for (int coin : coins) {
        for (int j = coin; j <= target; ++j) {
            dp[j] += dp[j - coin];
        }
    }

    return dp[target];
}

int main() {
    // Print the number of ways to make £2
    cout << ways_to_make_200() << endl;
    return 0;
}
