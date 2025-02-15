#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// function to check if a string is a palindrome
bool isPalindrome(const string &s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

// function to convert an integer to its binary representation (without the "0b" prefix)
string toBinary(int n) {
    string bin;
    while (n > 0) {
        bin.push_back((n % 2) + '0');
        n /= 2;
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

int main() {
    long long total = 0;

    // iterate over all numbers less than 1,000,000
    for (int n = 1; n < 1000000; n++) {
        string decimal = to_string(n);
        // check if the number is a palindrome in base 10
        if (isPalindrome(decimal)) {
            string binary = toBinary(n);
            // check if the number is a palindrome in base 2
            if (isPalindrome(binary)) {
                total += n;
            }
        }
    }

    cout << total << endl;
    return 0;
}
