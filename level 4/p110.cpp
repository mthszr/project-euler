#include <climits>
#include <iostream>
#include <vector>
using namespace std;

typedef unsigned long long ull;

ull best = ULLONG_MAX;          // smallest valid n found
const ull TARGET = 8000001ULL;  // required divisor count for n²

vector<ull> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};

// recursive function to build n using prime factorization
void search(int pos, int maxExp, ull currentN, ull currentDiv) {
    if (currentDiv >= TARGET) {  // found a valid n
        best = min(best, currentN);
        return;
    }
    if (pos >= primes.size()) return;  // out of primes

    for (int exp = 1; exp <= maxExp; exp++) {
        ull factor = 1;
        for (int i = 0; i < exp; i++) {
            if (currentN > best / primes[pos]) {
                factor = 0;
                break;
            }
            factor *= primes[pos];
        }
        if (factor == 0 || currentN > best / factor) break;

        ull newN = currentN * factor;
        ull newDiv = currentDiv * (2 * exp + 1);

        if (newN >= best) break;
        search(pos + 1, exp, newN, newDiv);
    }
}

int main() {
    search(0, 100, 1, 1);
    cout << "least value of n: " << best << endl;
    return 0;
}
