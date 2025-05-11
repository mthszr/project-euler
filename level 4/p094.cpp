#include <iostream>
using namespace std;

int main() {
    long long limit = 1000000000;
    long long totalSum = 0;

    // type1: triangles with sides (a,a,a+1)
    // recurrence: a_next = 14*a_curr - a_prev - 4
    long long a_prev = 5;          // first valid a
    long long a_curr = 65;         // second valid a
    long long p = 3 * a_prev + 1;  // perimeter = 3*a + 1
    if (p <= limit)
        totalSum += p;
    p = 3 * a_curr + 1;
    if (p <= limit)
        totalSum += p;
    while (true) {
        long long a_next = 14 * a_curr - a_prev - 4;
        p = 3 * a_next + 1;
        if (p > limit)
            break;
        totalSum += p;
        a_prev = a_curr;
        a_curr = a_next;
    }

    // type2: triangles with sides (a,a,a-1)
    // recurrence: a_next = 14*a_curr - a_prev + 4
    a_prev = 17;         // first valid a
    a_curr = 241;        // second valid a
    p = 3 * a_prev - 1;  // perimeter = 3*a - 1
    if (p <= limit)
        totalSum += p;
    p = 3 * a_curr - 1;
    if (p <= limit)
        totalSum += p;
    while (true) {
        long long a_next = 14 * a_curr - a_prev + 4;
        p = 3 * a_next - 1;
        if (p > limit)
            break;
        totalSum += p;
        a_prev = a_curr;
        a_curr = a_next;
    }

    cout << totalSum << endl;
    return 0;
}
