#include <algorithm>
#include <iostream>
#include <set>
#include <string>

using namespace std;

// Function to check if a given string is pandigital
bool is_pandigital(const string &str) {
    if (str.length() != 9) {
        return false;
    }
    string digits = "123456789";
    string sorted_str = str;
    sort(sorted_str.begin(), sorted_str.end());
    return sorted_str == digits;
}

int main() {
    set<int> unique_products;  // To store unique products
    int sum = 0;

    // Iterate through possible multiplicands and multipliers
    for (int multiplicand = 1; multiplicand < 100; ++multiplicand) {
        for (int multiplier = multiplicand + 1; multiplier < 5000; ++multiplier) {
            int product = multiplicand * multiplier;

            // Create the concatenated string
            string combined = to_string(multiplicand) + to_string(multiplier) + to_string(product);

            // Check if the combination is pandigital
            if (is_pandigital(combined)) {
                if (unique_products.find(product) == unique_products.end()) {
                    unique_products.insert(product);
                    sum += product;
                }
            }
        }
    }

    // Output the result
    cout << "The sum of all products is: " << sum << endl;

    return 0;
}
