#include <iostream>
#include <vector>

using namespace std;

// Function to calculate the sum of proper divisors of n
int sum_of_divisors(int n) {
    int sum = 1;  // 1 is always a divisor
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            sum += i;
            if (i != n / i) {
                sum += n / i;
            }
        }
    }
    return sum;
}

int main() {
    const int LIMIT = 10000;
    vector<bool> amicable(LIMIT, false);  // To mark numbers that are part of an amicable pair
    int total_sum = 0;

    // Iterate through all numbers less than 10000
    for (int a = 2; a < LIMIT; ++a) {
        if (!amicable[a]) {  // If a is not already part of an amicable pair
            int b = sum_of_divisors(a);
            if (b != a && b < LIMIT && sum_of_divisors(b) == a) {
                // If b is valid and d(b) = a, then a and b are amicable
                amicable[a] = true;
                amicable[b] = true;
                total_sum += a + b;
            }
        }
    }

    cout << "Sum of all amicable numbers under " << LIMIT << " is: " << total_sum << endl;

    return 0;
}
