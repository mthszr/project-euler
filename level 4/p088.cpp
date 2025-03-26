#include <climits>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

const int MAX_K = 12000;
const int N_MAX = 24000; 

vector<int> minimal_n(MAX_K + 1, INT_MAX);
unordered_set<int> unique_n;

void generate_combinations(vector<int>& current_factors, int start, int product_so_far, int sum_so_far, int t) {
    if (current_factors.size() == t) {
        int N = product_so_far;
        int S = sum_so_far;
        int m = N - S;
        int k = t + m;
        if (k >= 2 && k <= MAX_K && N < minimal_n[k]) {
            minimal_n[k] = N;
        }
        return;
    }

    if (product_so_far > N_MAX) return;

    int a_start = current_factors.empty() ? 2 : current_factors.back();
    for (int a = a_start; a <= N_MAX / product_so_far; ++a) {
        int next_product = product_so_far * a;
        if (next_product > N_MAX) break;
        int next_sum = sum_so_far + a;
        current_factors.push_back(a);
        generate_combinations(current_factors, a, next_product, next_sum, t);
        current_factors.pop_back();
    }
}

int main() {
    const int MAX_T = 20;  // Sufficient for N_MAX=24000

    for (int t = 2; t <= MAX_T; ++t) {
        vector<int> factors;
        generate_combinations(factors, 2, 1, 0, t);
    }

    for (int k = 2; k <= MAX_K; ++k) {
        if (minimal_n[k] != INT_MAX) {
            unique_n.insert(minimal_n[k]);
        }
    }

    long sum = 0;
    for (int num : unique_n) {
        sum += num;
    }

    cout << "Sum: " << sum << endl;
    return 0;
}