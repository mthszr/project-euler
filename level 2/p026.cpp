#include <iostream>
#include <vector>

using namespace std;

// Function to find the length of the repeating decimal cycle of 1/d
int getCycleLength(int d) {
    vector<int> remainders(d, -1);  // Keeps track of the remainders
    int remainder = 1;
    int position = 0;

    while (remainder != 0 && remainders[remainder] == -1) {
        remainders[remainder] = position;
        remainder = (remainder * 10) % d;
        position++;
    }

    // If remainder becomes 0, it means the decimal terminates
    if (remainder == 0) return 0;

    // Otherwise, we have found the cycle length
    return position - remainders[remainder];
}

int main() {
    int maxCycleLength = 0;
    int result = 0;

    for (int d = 2; d < 1000; d++) {
        int cycleLength = getCycleLength(d);
        if (cycleLength > maxCycleLength) {
            maxCycleLength = cycleLength;
            result = d;
        }
    }

    cout << "The value of d < 1000 for which 1/d has the longest repeating cycle is: " << result << endl;

    return 0;
}
