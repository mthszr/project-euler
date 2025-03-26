#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

// build the graph and in-degree map from the keylog triples.
void buildGraph(const vector<string>& triples,
                unordered_map<char, unordered_set<char>>& adj,
                unordered_map<char, int>& indeg) {
    // first, add every digit from every triple to adj and indeg.
    for (const auto& t : triples) {
        for (char d : t) {
            if (adj.find(d) == adj.end()) {
                // Initialize an empty set for this digit and indegree 0.
                adj[d] = unordered_set<char>();
                indeg[d] = 0;
            }
        }
    }
    // now add directed edges for each triple.
    for (const auto& t : triples) {
        char a = t[0], b = t[1], c = t[2];
        // if there's no edge from a to b yet, add it and increase indegree of b.
        if (adj[a].find(b) == adj[a].end()) {
            adj[a].insert(b);
            indeg[b]++;
        }
        // similarly, add edge from b to c.
        if (adj[b].find(c) == adj[b].end()) {
            adj[b].insert(c);
            indeg[c]++;
        }
    }
}

// perform a topological sort (Kahn's algorithm) to determine the passcode.
string topoSort(unordered_map<char, unordered_set<char>>& adj,
                unordered_map<char, int>& indeg) {
    queue<char> q;
    // push all digits with indegree 0.
    for (auto& p : indeg) {
        if (p.second == 0) {
            q.push(p.first);
        }
    }
    string order;
    while (!q.empty()) {
        char node = q.front();
        q.pop();
        order.push_back(node);
        // for each neighbor, reduce its indegree.
        for (char nxt : adj[node]) {
            indeg[nxt]--;
            if (indeg[nxt] == 0) {
                q.push(nxt);
            }
        }
    }
    return order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // the 50 keylog entries (each a successful login hint).
    vector<string> triples = {
        "319", "680", "180", "690", "129", "620", "762", "689",
        "762", "318", "368", "710", "720", "710", "629", "168",
        "160", "689", "716", "731", "736", "729", "316", "729",
        "729", "710", "769", "290", "719", "680", "318", "389",
        "162", "289", "162", "718", "729", "319", "790", "680",
        "890", "362", "319", "760", "316", "729", "380", "319",
        "728", "716"};

    unordered_map<char, unordered_set<char>> adj;
    unordered_map<char, int> indeg;

    // build the graph from the triples.
    buildGraph(triples, adj, indeg);

    // compute the topological order (the passcode).
    string passcode = topoSort(adj, indeg);

    cout << "Shortest passcode derived from keylog.txt: " << passcode << "\n";

    return 0;
}
