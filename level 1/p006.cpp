#include <iostream>
using namespace std;

int main() {
    int n = 100;

    // Calculate the sum of squares of the first n natural numbers
    long long sum_of_squares = (n * (n + 1) * (2 * n + 1)) / 6;

    // Calculate the square of the sum of the first n natural numbers
    long long sum = (n * (n + 1)) / 2;
    long long square_of_sum = sum * sum;

    // Calculate the difference
    long long difference = square_of_sum - sum_of_squares;

    // Output the result
    cout << "The difference is: " << difference << endl;

    return 0;
}
