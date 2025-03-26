#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Cell {
    int distance;
    int row;
    int col;
    Cell(int d, int r, int c) : distance(d), row(r), col(c) {}
};

struct CompareCell {
    bool operator()(const Cell& a, const Cell& b) {
        return a.distance > b.distance;  // min-heap based on distance
    }
};

int main() {
    vector<vector<int>> matrix;
    ifstream file("matrix.txt");
    string line;

    // read matrix from file
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

    vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
    priority_queue<Cell, vector<Cell>, CompareCell> pq;

    // initialize starting cell
    distance[0][0] = matrix[0][0];
    pq.push(Cell(distance[0][0], 0, 0));

    // directions: up, down, left, right
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();

        // check if current cell is the destination
        if (current.row == rows - 1 && current.col == cols - 1) {
            cout << current.distance << endl;
            return 0;
        }

        // skip if a shorter path has already been found
        if (current.distance > distance[current.row][current.col]) {
            continue;
        }

        // explore all four directions
        for (auto& dir : dirs) {
            int new_row = current.row + dir[0];
            int new_col = current.col + dir[1];

            // check if new position is within bounds
            if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols) {
                int new_distance = current.distance + matrix[new_row][new_col];

                // update if a shorter path is found
                if (new_distance < distance[new_row][new_col]) {
                    distance[new_row][new_col] = new_distance;
                    pq.push(Cell(new_distance, new_row, new_col));
                }
            }
        }
    }

    // if destination is unreachable (though problem states it's possible)
    cout << "destination not reached." << endl;
    return 0;
}