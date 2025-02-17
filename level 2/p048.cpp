#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    // define the modulus as 10^10
    const long long mod = 10000000000LL;
    long long result = 0;

    // iterate through numbers 1 to 1000
    for (int i = 1; i <= 1000; i++) {
        long long term = 1;
        // compute i^i modulo mod
        for (int j = 0; j < i; j++) {
            term = (term * i) % mod;
        }
        // add the term to the running total
        result = (result + term) % mod;
    }

    // output the last ten digits, padded with zeros if necessary
    cout << setw(10) << setfill('0') << result << endl;

    return 0;
}
