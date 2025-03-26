#include <iostream>
#include <vector>
using namespace std;

long long countReducedProperFractions(int max_d) {
    vector<long long> phi(max_d + 1);
    for (int i = 0; i <= max_d; ++i) {
        phi[i] = i;
    }

    for (int p = 2; p <= max_d; ++p) {
        if (phi[p] == p) {  // p is prime
            for (int multiple = p; multiple <= max_d; multiple += p) {
                phi[multiple] -= phi[multiple] / p;
            }
        }
    }

    long long total = 0;
    for (int d = 2; d <= max_d; ++d) {
        total += phi[d];
    }

    return total;
}

int main() {
    int max_d = 1000000;
    long long result = countReducedProperFractions(max_d);
    cout << result << endl;
    return 0;
}