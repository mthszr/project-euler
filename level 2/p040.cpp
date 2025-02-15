#include <iostream>
#include <string>
using namespace std;

int main() {
    // positions to check: 1, 10, 100, 1000, 10000, 100000, 1000000
    int positions[] = {1, 10, 100, 1000, 10000, 100000, 1000000};
    long long product = 1;

    // build the concatenated string of positive integers until its length
    // is at least the largest required position 
    string s = "";
    int num = 1;
    while (s.size() < positions[6]) {
        s += to_string(num);
        num++;
    }

    // for each required position, get the digit, using zero-based index)
    // and multiply it into the product
    for (int i = 0; i < 7; i++) {
        int pos = positions[i] - 1;  // convert to zero-based index
        int digit = s[pos] - '0';
        product *= digit;
    }

    cout << product << endl;  // prints 210
    return 0;
}
