#include <iostream>
using namespace std;

// Function to calculate the binomial coefficient
unsigned long long binomial_coefficient(int n, int k) {
    if (k > n - k)
        k = n - k;

    unsigned long long result = 1;
    for (int i = 0; i < k; ++i) {
        result *= (n - i);
        result /= (i + 1);
    }
    return result;
}

int main() {
    int grid_size = 20;

    // Calculate the number of routes in a 20x20 grid
    unsigned long long routes = binomial_coefficient(2 * grid_size, grid_size);

    // Print the result
    cout << "O número de caminhos através de uma grade 20x20 é: " << routes << endl;
    return 0;
}
