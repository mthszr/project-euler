#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    // Open the file containing base,exponent pairs
    ifstream file("base_exp.txt");
    if (!file.is_open()) return 1;

    string line;
    int best_line = 0;
    long double best_value = 0.0L;
    int current_line = 0;

    // read each line of the form base,exponent
    while (getline(file, line)) {
        ++current_line;
        stringstream ss(line);
        long long base, exponent;
        char comma;

        // parse base and exponent separated by comma
        ss >> base >> comma >> exponent;

        // compute comparison metric as exponent * log(base)
        long double val = exponent * logl((long double)base);

        // update best if this line has a larger value
        if (val > best_value) {
            best_value = val;
            best_line = current_line;
        }
    }

    file.close();

    // output the line number with the greatest numerical value
    cout << best_line << endl;
    return 0;
}
