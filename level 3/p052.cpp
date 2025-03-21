#include <algorithm>
#include <iostream>

using namespace std;

// function to check if two numbers have the same digits
bool same_digits(int a, int b) {
    string sa = to_string(a);
    string sb = to_string(b);
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    return sa == sb;
}

int main() {
    int x = 1;

    while (true) {
        // check if x, 2x, 3x, 4x, 5x, and 6x have the same digits
        if (same_digits(x, 2 * x) && same_digits(x, 3 * x) &&
            same_digits(x, 4 * x) && same_digits(x, 5 * x) &&
            same_digits(x, 6 * x)) {
            cout << x << endl;
            break;
        }
        x++;
    }

    return 0;
}
