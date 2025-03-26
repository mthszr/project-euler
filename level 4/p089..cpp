#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

string subtractive(const string& roman) {
    string result = roman;
    vector<pair<string, string>> replacements = {
        {"VIIII", "IX"},
        {"IIII", "IV"},
        {"LXXXX", "XC"},
        {"XXXX", "XL"},
        {"DCCCC", "CM"},
        {"CCCC", "CD"}};

    for (const auto& [old_str, new_str] : replacements) {
        size_t pos = 0;
        while ((pos = result.find(old_str, pos)) != string::npos) {
            result.replace(pos, old_str.length(), new_str);
            pos += new_str.length();
        }
    }

    return result;
}

int main() {
    ifstream file("roman.txt");
    if (!file.is_open()) {
        cerr << "error opening file." << endl;
        return 1;
    }

    int current = 0;
    int improved = 0;
    string line;

    while (getline(file, line)) {
        string roman = line;
        current += roman.length();
        improved += subtractive(roman).length();
    }

    file.close();
    cout << (current - improved) << endl;

    return 0;
}