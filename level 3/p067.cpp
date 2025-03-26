#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    // open the file containing the triangle
    ifstream fin("triangle.txt");
    if (!fin) {
        cerr << "error opening file" << endl;
        return 1;
    }

    // read the triangle from the file into a 2d vector
    vector<vector<int>> triangle;
    string line;
    while (getline(fin, line)) {
        // use istringstream to parse numbers in the line
        istringstream iss(line);
        vector<int> row;
        int number;
        while (iss >> number) {
            row.push_back(number);
        }
        triangle.push_back(row);
    }
    fin.close();

    // use dynamic programming from bottom up to compute maximum path sum
    // start from the second last row and update each number with the sum of itself and
    // the maximum of its two adjacent numbers in the row below
    for (int i = triangle.size() - 2; i >= 0; i--) {
        for (int j = 0; j < triangle[i].size(); j++) {
            triangle[i][j] += max(triangle[i + 1][j], triangle[i + 1][j + 1]);
        }
    }

    // the top element now contains the maximum total from top to bottom
    cout << "maximum total from top to bottom is: " << triangle[0][0] << endl;

    return 0;
}
