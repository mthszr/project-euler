#include <iostream>
using namespace std;

// function to reverse a number
long long reverse_number(long long n) {
    long long reversed = 0;
    while (n > 0) {
        reversed = reversed * 10 + (n % 10);
        n /= 10;
    }
    return reversed;
}

// function to check if a number is a palindrome
bool is_palindrome(long long n) {
    return n == reverse_number(n);
}

// function to determine if a number is a lychrel number
bool is_lychrel(int n) {
    long long current = n;
    for (int i = 0; i < 50; i++) {
        current += reverse_number(current);
        if (is_palindrome(current)) {
            return false;  // found a palindrome, not a lychrel number
        }
    }
    return true;  // did not find a palindrome within 50 iterations
}

int main() {
    int count = 0;
    for (int i = 1; i < 10000; i++) {
        if (is_lychrel(i)) {
            count++;
        }
    }
    cout << count << endl;
    return 0;
}
