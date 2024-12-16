#include <cmath>
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Calculate 2^1000 as a string
    string number = to_string(pow(2, 1000));

    // Variable to store the sum of digits
    int sum = 0;

    // Iterate through each character of the string (each digit)
    for (char digit : number) {
        sum += digit - '0';  // Convert char to int and add to sum
    }

    // Output the result
    cout << "The sum of the digits of 2^1000 is: " << sum << endl;
    return 0;
}
