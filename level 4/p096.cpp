#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int board[9][9];
bool row_used[9][10], col_used[9][10], box_used[9][10];

// Initialize usage trackers for rows, columns, and boxes
void initialize_trackers() {
    for (int i = 0; i < 9; ++i)
        for (int d = 1; d <= 9; ++d)
            row_used[i][d] = col_used[i][d] = box_used[i][d] = false;
}

// Compute the box index (0 to 8) for a given cell
int get_box_index(int r, int c) {
    return (r / 3) * 3 + (c / 3);
}

// Backtracking solver
bool solve_sudoku(int r, int c) {
    if (r == 9) return true;  // all rows filled
    if (c == 9) return solve_sudoku(r + 1, 0);
    if (board[r][c] != 0)
        return solve_sudoku(r, c + 1);

    int b = get_box_index(r, c);
    for (int digit = 1; digit <= 9; ++digit) {
        if (!row_used[r][digit] && !col_used[c][digit] && !box_used[b][digit]) {
            // place digit
            board[r][c] = digit;
            row_used[r][digit] = col_used[c][digit] = box_used[b][digit] = true;
            if (solve_sudoku(r, c + 1))
                return true;
            // backtrack
            board[r][c] = 0;
            row_used[r][digit] = col_used[c][digit] = box_used[b][digit] = false;
        }
    }
    return false;
}

int main() {
    ifstream fin("sudoku.txt");
    if (!fin) {
        cerr << "Error: could not open sudoku.txt\n";
        return 1;
    }

    int total_sum = 0;
    string line;

    for (int puzzle = 0; puzzle < 50; ++puzzle) {
        // skip any blank lines and read the "Grid XX" label
        do {
            if (!getline(fin, line)) {
                cerr << "Unexpected end of file\n";
                return 1;
            }
        } while (line.empty());

        // now read the 9 rows of digits
        initialize_trackers();
        for (int i = 0; i < 9; ++i) {
            getline(fin, line);
            for (int j = 0; j < 9; ++j) {
                int d = line[j] - '0';
                board[i][j] = d;
                if (d != 0) {
                    int b = get_box_index(i, j);
                    row_used[i][d] = col_used[j][d] = box_used[b][d] = true;
                }
            }
        }

        // solve and add top-left 3-digit number
        solve_sudoku(0, 0);
        int top_left = board[0][0] * 100 + board[0][1] * 10 + board[0][2];
        total_sum += top_left;
    }

    cout << total_sum << "\n";
    return 0;
}
