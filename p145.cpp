#include <iostream>
using namespace std;
typedef long long ll;

// function to compute integer power: base^exp
ll ipow(ll base, int exp) {
    ll result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

int main() {
    ll total = 0;

    /*
    
    - there are no 1-digit solutions.

    - for a two-digit number (ab):
      - a + b must be odd and less than 10, with neither a nor b zero.
      - this gives 20 valid pairs.

    - for a three-digit number (abc):
      - we have 5 choices for the middle digit b (such that 2b < 10)
      - and 20 choices for the pair (a, c) such that a + c is odd and greater than 10.
      - in total, 5 * 20 = 100 solutions.

    - for a four-digit number (abcd):
      - a + d must be odd and less than 10 (with a and d nonzero) giving 20 choices,
      - and b + c must be odd and less than 10 giving 30 choices.
      - total solutions: 20 * 30 = 600.

    - there are no 5-digit solutions.

    - for a six-digit number (abcdef):
      - the conditions on pairs (a, f), (b, e), and (c, d) each yield:
        for (a, f): 20 choices (a+f odd, a,f nonzero),
        for (b, e) and (c, d): 30 choices each.
      - total solutions: 20 * 30 * 30 = 18000.

    - for a seven-digit number (abcdefg):
      - the conditions give:
          5 choices for the middle digit d (since 2d < 10),
          20 choices for (a, g) with a+g odd and greater than 10,
          25 choices for (b, f) with b+f even and greater than 10,
          20 choices for (c, e) with c+e odd and greater than 10.
      - total solutions: 5 * 20 * 25 * 20 = 50000.

    - for an eight-digit number (abcdefgh):
      - similar to even-digit cases:
          for 2n-digit numbers (here n = 4): count = 20 * 30^(n-1)
      - so for eight digits: 20 * 30^(4-1) = 20 * 30^3 = 540000.

    - there are no 9-digit solutions.

    thus, reversible numbers below one billion (10^9) come from:
      2-digit:     20
      3-digit:     100
      4-digit:     600
      6-digit:     18000
      7-digit:     50000
      8-digit:     540000

    total = 20 + 100 + 600 + 18000 + 50000 + 540000 = 608720.
    */

    // even-digit solutions (2, 4, 6, 8-digit numbers)
    // formula: for 2n-digit numbers, count = 20 * 30^(n-1)
    for (int d = 2; d <= 8; d += 2) {
        int n = d / 2;
        ll count = 20 * ipow(30, n - 1);
        total += count;
    }

    // odd-digit solutions (3 and 7-digit numbers)
    // formula: for (4n+3)-digit numbers, count = 5 * 20^(n+1) * 25^n
    for (int d = 3; d <= 7; d += 4) {
        int n = (d - 3) / 4;  
        ll count = 5 * ipow(20, n + 1) * ipow(25, n);
        total += count;
    }

    cout << total << endl; 
    return 0;
}
