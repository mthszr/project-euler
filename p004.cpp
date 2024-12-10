#include <algorithm>  // for reverse function
#include <iostream>

using namespace std;

// Function to check if a number is a palindrome
bool is_palindrome(int num) {
    string str = to_string(num);
    string reversed_str = str;
    reverse(reversed_str.begin(), reversed_str.end());
    return str == reversed_str;
}

int main() {
    int largest_palindrome = 0;

    // Iterate over the product of two 3-digit numbers
    for (int i = 999; i >= 100; i--) {
        for (int j = i; j >= 100; j--) {
            int product = i * j;
            // Check if the product is a palindrome and larger than the current largest
            if (is_palindrome(product) && product > largest_palindrome) {
                largest_palindrome = product;
            }
        }
    }

    cout << "The largest palindrome made from the product of two 3-digit numbers is " << largest_palindrome << endl;
    return 0;
}
