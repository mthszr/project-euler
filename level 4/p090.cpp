#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

vector<vector<int>> generate_all_cubes() {
    vector<vector<int>> cubes;
    vector<int> digits = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<bool> bitmask(10, false);
    fill(bitmask.begin(), bitmask.begin() + 6, true);
    do {
        vector<int> cube;
        for (int i = 0; i < 10; ++i) {
            if (bitmask[i]) {
                cube.push_back(digits[i]);
            }
        }
        cubes.push_back(cube);
    } while (prev_permutation(bitmask.begin(), bitmask.end()));
    return cubes;
}

bool check_square(int d1, int d2, const set<int>& cube1_ext, const set<int>& cube2_ext) {
    vector<int> d1_options;
    if (d1 == 6 || d1 == 9) {
        d1_options = {6, 9};
    } else {
        d1_options = {d1};
    }
    vector<int> d2_options;
    if (d2 == 6 || d2 == 9) {
        d2_options = {6, 9};
    } else {
        d2_options = {d2};
    }

    for (int a : d1_options) {
        for (int b : d2_options) {
            if ((cube1_ext.count(a) && cube2_ext.count(b)) ||
                (cube2_ext.count(a) && cube1_ext.count(b))) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    vector<vector<int>> cubes = generate_all_cubes();
    vector<pair<int, int>> squares = {
        {0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};

    int count = 0;
    for (size_t i = 0; i < cubes.size(); ++i) {
        const auto& cube1 = cubes[i];
        set<int> cube1_ext;
        for (int d : cube1) {
            cube1_ext.insert(d);
            if (d == 6) cube1_ext.insert(9);
            if (d == 9) cube1_ext.insert(6);
        }
        for (size_t j = i; j < cubes.size(); ++j) {
            const auto& cube2 = cubes[j];
            set<int> cube2_ext;
            for (int d : cube2) {
                cube2_ext.insert(d);
                if (d == 6) cube2_ext.insert(9);
                if (d == 9) cube2_ext.insert(6);
            }
            bool valid = true;
            for (const auto& square : squares) {
                int d1 = square.first;
                int d2 = square.second;
                if (!check_square(d1, d2, cube1_ext, cube2_ext)) {
                    valid = false;
                    break;
                }
            }
            if (valid) {
                ++count;
            }
        }
    }

    cout << count << endl;
    return 0;
}