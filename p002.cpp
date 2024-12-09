#include <iostream>

int main() {
    // Initialize the first two terms of the Fibonacci sequence
    long long int a = 1, b = 2;
    long long int sum = 0;

    // Loop through the Fibonacci sequence
    while (b <= 4000000) {
        // If the term is even, add it to the sum
        if (b % 2 == 0) {
            sum += b;
        }

        // Update the Fibonacci terms
        long long int temp = a + b;
        a = b;
        b = temp;
    }

    // Output the result
    std::cout << "The sum of the even-valued Fibonacci terms below 4 million is: " << sum << std::endl;

    return 0;
}
