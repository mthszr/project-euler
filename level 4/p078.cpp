#include <iostream>
#include <vector>

using namespace std;

// function to compute generalized pentagonal numbers
int pentagonal(int k) {
    return k * (3 * k - 1) / 2;
}

int findLeastN() {
    const int MOD = 1000000;
    vector<int> p = {1};  // p(0) = 1

    int n = 1;
    while (true) {
        int pn = 0;
        for (int k = 1;; ++k) {
            int gk = pentagonal(k);
            if (gk > n) break;
            if (k % 2 == 1) {
                pn += p[n - gk];
            } else {
                pn -= p[n - gk];
            }
            gk = pentagonal(-k);
            if (gk > n) break;
            if (k % 2 == 1) {
                pn += p[n - gk];
            } else {
                pn -= p[n - gk];
            }
            pn %= MOD;
        }
        if (pn < 0) pn += MOD;
        p.push_back(pn);
        if (pn == 0) {
            return n;
        }
        ++n;
    }
}

int main() {
    int result = findLeastN();
    cout << "the least value of n for which p(n) is divisible by one million is " << result << endl;
    return 0;
}