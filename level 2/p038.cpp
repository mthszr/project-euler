#include <iostream>
#include <string>
using namespace std;

// function to check if a string is 1 to 9 pandigital
bool isPandigital(const string &s) {
    if (s.size() != 9) return false;
    // create an array to mark digits 1 to 9 (index 0 unused)
    bool seen[10] = {false};
    for (char ch : s) {
        if (ch == '0') return false;  // no zeros allowed
        int digit = ch - '0';
        if (seen[digit]) return false;
        seen[digit] = true;
    }
    return true;
}

int main() {
    int largest = 0;

    // we can search for x in a reasonable range.
    // note: if x has 5 or more digits, then x*1 already has at least 5 digits,
    // and the concatenated product with n>=2 would exceed 9 digits.
    // so we search for x from 1 to 9999.
    for (int i = 1; i < 10000; i++) {
        string concatenated = "";
        int n = 1;
        // build the concatenated product until its length is at least 9
        while (concatenated.size() < 9) {
            concatenated += to_string(i * n);
            n++;
        }
        // if we got exactly 9 digits and it's pandigital, update the largest value
        if (concatenated.size() == 9 && isPandigital(concatenated)) {
            int candidate = stoi(concatenated);
            if (candidate > largest) {
                largest = candidate;
            }
        }
    }

    cout << largest << endl;  
    return 0;
}
