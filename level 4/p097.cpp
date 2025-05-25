#include <cstdint>
#include <iomanip>
#include <iostream>

using namespace std;

int main() {
    const uint64_t MOD = 10000000000ULL;  // 10^10
    const uint64_t base = 2;
    const uint64_t exponent = 7830457;
    const uint64_t multiplier = 28433;

    // fast exponentiation: compute (base^exponent) % MOD
    uint64_t result = 1;
    uint64_t b = base % MOD;
    uint64_t e = exponent;
    while (e > 0) {
        if (e & 1) {
            __int128 tmp = (__int128)result * b;
            result = (uint64_t)(tmp % MOD);
        }
        __int128 tmp = (__int128)b * b;
        b = (uint64_t)(tmp % MOD);
        e >>= 1;
    }

    // multiply by 28433, add 1, then take mod again
    __int128 res2 = (__int128)result * multiplier + 1;
    uint64_t answer = (uint64_t)(res2 % MOD);

    // print with leading zeros if necessary
    cout << setw(10) << setfill('0') << answer << "\n";
    return 0;
}
