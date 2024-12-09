#include <iostream>
using namespace std;

int main() {
    int sum = 0;

    // Loop through all numbers below 1000
    for (int i = 1; i < 1000; i++) {
        // Check if the number is a multiple of 3 or 5
        if (i % 3 == 0 || i % 5 == 0) {
            sum += i; // Add the number to the sum
        }
    }

    cout << "The sum of all multiples of 3 or 5 below 1000 is: " << sum << endl;

    return 0;
}
