#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main() {
  
    // read words from file and store them in array
    const int MAXW = 2000;
    string words[MAXW];
    int total = 0;
    ifstream file("words.txt");
    if (!file.is_open()) return 1;
    string line;
    getline(file, line);
    file.close();
    stringstream ss(line);
    string token;
    while (getline(ss, token, ',') && total < MAXW) {
        // remove quotes
        words[total++] = token.substr(1, token.size() - 2);
    }

    int max_square = 0;

    // loop over all unique word pairs
    for (int i = 0; i < total; ++i) {
        for (int j = i + 1; j < total; ++j) {
            string &a = words[i];
            string &b = words[j];
            int len = a.length();
            if (len != (int)b.length()) continue;

            // check if they are anagrams
            string sa = a, sb = b;
            sort(sa.begin(), sa.end());
            sort(sb.begin(), sb.end());
            if (sa != sb) continue;

            // compute square root range for len-digit numbers
            int start = (int)ceil(sqrt(pow(10, len - 1)));
            int end = (int)floor(sqrt(pow(10, len) - 1));

            // try all squares in range as mapping for first word
            for (int k = start; k <= end; ++k) {
                int sq = k * k;
                string s_sq = to_string(sq);

                // map letters in a to digits
                int map[26];
                bool used[10];
                for (int x = 0; x < 26; ++x) map[x] = -1;
                for (int x = 0; x < 10; ++x) used[x] = false;

                bool valid = true;
                for (int p = 0; p < len; ++p) {
                    int idx = a[p] - 'A';
                    int d = s_sq[p] - '0';
                    if (map[idx] == -1) {
                        if (used[d]) {
                            valid = false;
                            break;
                        }
                        map[idx] = d;
                        used[d] = true;
                    } else if (map[idx] != d) {
                        valid = false;
                        break;
                    }
                }
                if (!valid || s_sq[0] == '0') continue;

                // apply mapping to second word
                string mapped_b = "";
                for (int p = 0; p < len; ++p) {
                    int idx = b[p] - 'A';
                    if (map[idx] < 0) {
                        valid = false;
                        break;
                    }
                    mapped_b += char('0' + map[idx]);
                }
                if (!valid || mapped_b[0] == '0') continue;

                // check if mapped_b is a perfect square
                int qb = stoi(mapped_b);
                int r = (int)(sqrt(qb) + 0.5);
                if (r * r == qb) {
                    if (sq > max_square) max_square = sq;
                    if (qb > max_square) max_square = qb;
                }
            }
        }
    }

    cout << max_square << endl;
    return 0;
}
