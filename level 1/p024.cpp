#include <iostream>
#include <vector>

using namespace std;

int factorial(int n) {
    int fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    // Initialize digits and target
    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int k = 999999;  // 1,000,000th permutation, but 0-based index
    string result = "";

    // Loop through each position in the permutation
    for (int i = 9; i >= 0; --i) {
        int fact = factorial(i);
        int index = k / fact;  // Determine the index of the digit
        result += to_string(digits[index]);
        digits.erase(digits.begin() + index);  // Remove the digit from the list
        k %= fact;                             // Update k for the remaining permutation
    }

    cout << "The millionth lexicographic permutation is: " << result << endl;

    return 0;
}
