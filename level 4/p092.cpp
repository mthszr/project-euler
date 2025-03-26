#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, bool> terminators;

// function to calculate the sum of the squares of the digits
int sum_of_squares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;
        sum += digit * digit;
        n /= 10;
    }
    return sum;
}

// function to classify the number by sorting its digits as a string
string classify(int n) {
    string s = to_string(n);
    sort(s.begin(), s.end());
    return s;
}

// function to generate the chain and check if it ends at 89
bool chain(int start) {
    int n = start;
    int prev = -1;
    string key;
    vector<string> sequence;

    // continue the chain until reaching 1 or 89
    while (prev != 1 && prev != 89) {
        key = classify(n);
        sequence.push_back(key);

        // check if the result for this classification is already known
        if (terminators.find(key) != terminators.end()) {
            bool result = terminators[key];
            // store the result for the entire sequence
            for (const auto& num : sequence) {
                terminators[num] = result;
            }
            return result;
        }

        prev = n;
        n = sum_of_squares(n);
    }

    // store the final result for the entire sequence
    bool result = (prev == 89);
    for (const auto& num : sequence) {
        terminators[num] = result;
    }
    return result;
}

int main() {
    int count = 0;
    // iterate through numbers from 1 to 10 million
    for (int i = 1; i < 10000000; ++i) {
        if (chain(i)) {
            ++count;
        }
    }
    // print the final count of numbers ending in 89
    cout << count << endl;
    return 0;
}
