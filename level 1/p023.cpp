#include <iostream>
#include <vector>

// Function to calculate the sum of proper divisors of a number
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

// Function to find all abundant numbers up to a given limit
std::vector<int> find_abundant_numbers(int limit) {
    std::vector<int> abundant_numbers;
    for (int i = 12; i < limit; ++i) {
        if (sum_of_divisors(i) > i) {
            abundant_numbers.push_back(i);
        }
    }
    return abundant_numbers;
}

// Main function to solve the problem
int solve(int limit = 28123) {
    // Step 1: Find all abundant numbers up to the limit
    std::vector<int> abundant_numbers = find_abundant_numbers(limit);

    // Step 2: Create a boolean array to mark which numbers can be written as the sum of two abundant numbers
    std::vector<bool> can_be_written_as_sum(limit + 1, false);

    // Step 3: Mark all numbers that can be written as the sum of two abundant numbers
    for (int i = 0; i < abundant_numbers.size(); ++i) {
        for (int j = i; j < abundant_numbers.size(); ++j) {
            int abundant_sum = abundant_numbers[i] + abundant_numbers[j];
            if (abundant_sum <= limit) {
                can_be_written_as_sum[abundant_sum] = true;
            }
        }
    }

    // Step 4: Calculate the sum of all numbers that cannot be written as the sum of two abundant numbers
    int total_sum = 0;
    for (int i = 1; i <= limit; ++i) {
        if (!can_be_written_as_sum[i]) {
            total_sum += i;
        }
    }

    return total_sum;
}

int main() {
    // Running the solution with the default limit
    int result = solve();
    std::cout << "The sum of all the positive integers which cannot be written as the sum of two abundant numbers: " << result << std::endl;

    return 0;
}
