#include <iostream>
using namespace std;

int main() {
    int a, b, c;

    // Iterate through possible values of a
    for (a = 1; a < 1000; a++) {
        // Iterate through possible values of b, ensuring b > a
        for (b = a + 1; b < 1000 - a; b++) {
            // Calculate c based on a + b + c = 1000
            c = 1000 - a - b;

            // Check if it satisfies the Pythagorean theorem
            if (a * a + b * b == c * c) {
                cout << "The Pythagorean triplet is: a = " << a
                     << ", b = " << b
                     << ", c = " << c << endl;
                cout << "The product abc is: " << a * b * c << endl;
                return 0; 
            }
        }
    }

    cout << "No Pythagorean triplet found." << endl;
    return 0;
}
