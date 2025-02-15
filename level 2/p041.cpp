#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

// function to check if a number is prime
bool isprime(int n) {
    if (n < 2)
        return false;
    if (n % 2 == 0)
        return n == 2;
    int limit = sqrt(n);
    for (int i = 3; i <= limit; i += 2)
        if (n % i == 0)
            return false;
    return true;
}

int main() {
    // only need to check 7-digit pandigital numbers
    // because 8- and 9-digit pandigital numbers are divisible by 3
    // and the largest pandigital prime is known to be 7-digit
    string digits = "7654321";  // largest arrangement for 7-digit pandigital
    int maxprime = 0;

    // generate pandigital numbers in descending order
    do {
        int num = stoi(digits);
        if (isprime(num)) {
            maxprime = num;
            break;  // the first prime we find is the largest
        }
    } while (prev_permutation(digits.begin(), digits.end()));

    cout << maxprime << endl; 
    return 0;
}
