#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Function to calculate the alphabetical value of a name
int alphabetical_value(const string& name) {
    int sum = 0;
    for (char c : name) {
        sum += (c - 'A' + 1);  // Convert character to its alphabetical position
    }
    return sum;
}

int main() {
    ifstream file("names.txt");  // Replace with your file path
    string line;
    vector<string> names;

    // Read the file and store names
    if (file.is_open()) {
        getline(file, line);  // Read the first line (the list of names)
        file.close();

        // Split the line into individual names
        stringstream ss(line);
        string name;
        while (getline(ss, name, ',')) {
            // Remove quotes around the names
            name.erase(remove(name.begin(), name.end(), '"'), name.end());
            names.push_back(name);
        }
    } else {
        cout << "Unable to open file." << endl;
        return 1;
    }

    // Sort the names alphabetically
    sort(names.begin(), names.end());

    long long total_score = 0;

    // Calculate the name score for each name
    for (int i = 0; i < names.size(); ++i) {
        int name_value = alphabetical_value(names[i]);
        total_score += (i + 1) * name_value;  // Position is i+1 since the list is 0-indexed
    }

    cout << "Total of all name scores: " << total_score << endl;

    return 0;
}
