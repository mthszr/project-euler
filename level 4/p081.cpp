#include <algorithm>
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

    // Read the matrix from the file
    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(stoi(cell));
        }
        matrix.push_back(row);
    }

    int size = matrix.size();
    if (size == 0) {
        cout << "Empty matrix." << endl;
        return 0;
    }

    vector<vector<int>> dp(size, vector<int>(size, 0));
    dp[0][0] = matrix[0][0];

    // Initialize the first row
    for (int j = 1; j < size; ++j) {
        dp[0][j] = dp[0][j - 1] + matrix[0][j];
    }

    // Initialize the first column
    for (int i = 1; i < size; ++i) {
        dp[i][0] = dp[i - 1][0] + matrix[i][0];
    }

    // Fill the DP table
    for (int i = 1; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + matrix[i][j];
        }
    }

    cout << dp[size - 1][size - 1] << endl;

    return 0;
}