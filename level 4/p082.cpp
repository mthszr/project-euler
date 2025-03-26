#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> matrix;
    ifstream file("matrix.txt");
    string line;

    // read the matrix from the file
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }
        matrix.push_back(row);
    }

    int rows = matrix.size();
    if (rows == 0) {
        cout << "empty matrix." << endl;
        return 0;
    }
    int cols = matrix[0].size();

    // initialize dp with the first column
    vector<int> dp(rows);
    for (int i = 0; i < rows; ++i) {
        dp[i] = matrix[i][0];
    }

    // process each column starting from the second
    for (int j = 1; j < cols; ++j) {
        // create a temporary array for current column
        vector<int> temp(rows);
        for (int i = 0; i < rows; ++i) {
            temp[i] = dp[i] + matrix[i][j];
        }

        // top-down pass: check moving down from previous rows
        for (int i = 1; i < rows; ++i) {
            temp[i] = min(temp[i], temp[i - 1] + matrix[i][j]);
        }

        // bottom-up pass: check moving up from next rows
        for (int i = rows - 2; i >= 0; --i) {
            temp[i] = min(temp[i], temp[i + 1] + matrix[i][j]);
        }

        dp = temp;
    }

    // find the minimum value in the last column
    int min_sum = INT_MAX;
    for (int val : dp) {
        if (val < min_sum) {
            min_sum = val;
        }
    }

    cout << min_sum << endl;

    return 0;
}