#include <functional>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Function to check if two numbers are cyclic
bool is_cyclic(int x, int y) {
    return (x % 100) == (y / 100);
}

// Function to generate polygonal numbers
vector<pair<int, string>> generate_polygonal(int (*formula)(int), const string& type) {
    vector<pair<int, string>> result;
    for (int n = 1;; ++n) {
        int num = formula(n);
        if (num > 9999) break;                            // Stop when numbers exceed 4 digits
        if (num >= 1000) result.emplace_back(num, type);  // Include only 4-digit numbers
    }
    return result;
}

// Polygonal formulas
int triangle(int n) { return n * (n + 1) / 2; }
int square(int n) { return n * n; }
int pentagonal(int n) { return n * (3 * n - 1) / 2; }
int hexagonal(int n) { return n * (2 * n - 1); }
int heptagonal(int n) { return n * (5 * n - 3) / 2; }
int octagonal(int n) { return n * (3 * n - 2); }

// Custom hash function for std::pair<int, string>
struct pair_hash {
    template <typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& p) const {
        return hash<T1>()(p.first) ^ (hash<T2>()(p.second) << 1);
    }
};

int main() {
    // Generate all polygonal numbers
    vector<pair<int, string>> triangle_nums = generate_polygonal(triangle, "triangle");
    vector<pair<int, string>> square_nums = generate_polygonal(square, "square");
    vector<pair<int, string>> pentagonal_nums = generate_polygonal(pentagonal, "pentagonal");
    vector<pair<int, string>> hexagonal_nums = generate_polygonal(hexagonal, "hexagonal");
    vector<pair<int, string>> heptagonal_nums = generate_polygonal(heptagonal, "heptagonal");
    vector<pair<int, string>> octagonal_nums = generate_polygonal(octagonal, "octagonal");

    // Combine all numbers into a single vector
    vector<pair<int, string>> all_shapes;
    all_shapes.insert(all_shapes.end(), triangle_nums.begin(), triangle_nums.end());
    all_shapes.insert(all_shapes.end(), square_nums.begin(), square_nums.end());
    all_shapes.insert(all_shapes.end(), pentagonal_nums.begin(), pentagonal_nums.end());
    all_shapes.insert(all_shapes.end(), hexagonal_nums.begin(), hexagonal_nums.end());
    all_shapes.insert(all_shapes.end(), heptagonal_nums.begin(), heptagonal_nums.end());
    all_shapes.insert(all_shapes.end(), octagonal_nums.begin(), octagonal_nums.end());

    // Create a map to store cyclic connections
    unordered_map<pair<int, string>, vector<pair<int, string>>, pair_hash> cyclic_map;
    for (auto& x : all_shapes) {
        for (auto& y : all_shapes) {
            if (x.first != y.first && x.second != y.second && is_cyclic(x.first, y.first)) {
                cyclic_map[x].push_back(y);
            }
        }
    }

    // Search for the cyclic set
    for (auto& a : octagonal_nums) {
        for (auto& b : cyclic_map[a]) {
            for (auto& c : cyclic_map[b]) {
                for (auto& d : cyclic_map[c]) {
                    for (auto& e : cyclic_map[d]) {
                        for (auto& f : cyclic_map[e]) {
                            if (is_cyclic(f.first, a.first)) {
                                set<string> shapes = {a.second, b.second, c.second, d.second, e.second, f.second};
                                if (shapes.size() == 6) {  // Ensure all shapes are unique
                                    int sum = a.first + b.first + c.first + d.first + e.first + f.first;
                                    cout << sum << endl;
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
