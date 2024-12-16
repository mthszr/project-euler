#include <iostream>
#include <map>
#include <string>

using namespace std;

// Function to calculate the number of letters in a number written in words
int calculate_letters(int number, const map<int, string>& words) {
    if (number == 1000) {
        return words.at(1000).length();  // "one thousand" without spaces or hyphens
    }

    int letters = 0;

    if (number >= 100) {
        letters += words.at(number / 100).length();  // add letters for "x hundred"
        letters += words.at(100).length();
        if (number % 100 != 0) {
            letters += 3;  // add letters for "and"
        }
        number %= 100;  // reduce number to the remainder
    }

    if (number >= 20) {
        letters += words.at((number / 10) * 10).length();  // add the tens part
        number %= 10;                                      // reduce to the units
    }

    if (number > 0) {
        letters += words.at(number).length();  // add the units part
    }

    return letters;
}

int main() {
    // Words for the numbers
    map<int, string> words = {
        {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}, {10, "ten"}, {11, "eleven"}, {12, "twelve"}, {13, "thirteen"}, {14, "fourteen"}, {15, "fifteen"}, {16, "sixteen"}, {17, "seventeen"}, {18, "eighteen"}, {19, "nineteen"}, {20, "twenty"}, {30, "thirty"}, {40, "forty"}, {50, "fifty"}, {60, "sixty"}, {70, "seventy"}, {80, "eighty"}, {90, "ninety"}, {100, "hundred"}, {1000, "onethousand"}};

    int total_letters = 0;

    for (int i = 1; i <= 1000; ++i) {
        total_letters += calculate_letters(i, words);
    }

    cout << "Total letters used from 1 to 1000: " << total_letters << endl;

    return 0;
}
