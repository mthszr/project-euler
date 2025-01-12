#include <iostream>
#include <numeric>  // For gcd function

using namespace std;

// Function to check if a fraction is a curious fraction
bool is_curious_fraction(int numerator, int denominator) {
    // Convert numbers to strings
    string num = to_string(numerator);
    string den = to_string(denominator);

    // Check for trivial cases
    if (num[1] == '0' && den[1] == '0') {
        return false;
    }

    // Check if canceling a common digit results in equivalent fractions
    for (char digit : num) {
        if (digit != '0' && den.find(digit) != string::npos) {
            string new_num = num;
            string new_den = den;

            // Remove the common digit
            new_num.erase(new_num.find(digit), 1);
            new_den.erase(new_den.find(digit), 1);

            // Ensure the new strings are valid numbers
            if (!new_num.empty() && !new_den.empty()) {
                int reduced_num = stoi(new_num);
                int reduced_den = stoi(new_den);

                // Check if the fractions are equivalent
                if (numerator * reduced_den == denominator * reduced_num) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    int product_numerator = 1;
    int product_denominator = 1;

    // Iterate through all two-digit numerators and denominators
    for (int numerator = 10; numerator < 100; ++numerator) {
        for (int denominator = numerator + 1; denominator < 100; ++denominator) {
            if (is_curious_fraction(numerator, denominator)) {
                product_numerator *= numerator;
                product_denominator *= denominator;
            }
        }
    }

    // Simplify the product to its lowest terms
    int gcd_value = gcd(product_numerator, product_denominator);
    product_denominator /= gcd_value;

    // Output the denominator of the simplified product
    cout << "The value of the denominator is: " << product_denominator << endl;

    return 0;
}
