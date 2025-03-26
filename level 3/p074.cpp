#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Precompute factorials of digits 0-9
vector<int> factorial = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

int sumOfDigitFactorials(int n) {
    int sum = 0;
    while (n > 0) {
        sum += factorial[n % 10];
        n /= 10;
    }
    return sum;
}

int getChainLength(int n, unordered_map<int, int>& memo) {
    if (memo.find(n) != memo.end()) {
        return memo[n];
    }

    unordered_map<int, int> chain;
    int current = n;
    int length = 0;

    while (chain.find(current) == chain.end()) {
        chain[current] = length;
        current = sumOfDigitFactorials(current);
        length++;
    }

    for (auto& pair : chain) {
        memo[pair.first] = length - chain[pair.first];
    }

    return length;
}

int main() {
    unordered_map<int, int> memo;
    int count = 0;

    for (int i = 1; i < 1000000; ++i) {
        if (getChainLength(i, memo) == 60) {
            count++;
        }
    }

    cout << count << endl;
    return 0;
}