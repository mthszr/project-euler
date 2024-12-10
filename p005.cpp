#include <iostream>
using namespace std;

// Function to find the greatest common divisor (GCD)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the least common multiple (LCM) using GCD
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int result = 1;

    // Calculate the LCM of numbers from 1 to 20
    for (int i = 1; i <= 20; i++) {
        result = lcm(result, i);
    }

    cout << "The smallest number divisible by all numbers from 1 to 20 is " << result << endl;
    return 0;
}
