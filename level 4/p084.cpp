#include <algorithm>
#include <ctime>
#include <deque>
#include <iostream>
#include <map>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// define board squares and their indices
vector<string> squares = {
    "GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3",
    "JAIL", "C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3",
    "FP", "E1", "CH2", "E2", "E3", "R3", "F1", "F2", "U2", "F3",
    "G2J", "G1", "G2", "CC3", "G3", "R4", "CH3", "H1", "T2", "H2"};

map<string, int> square_numbers;
const int num_squares = 40;

// initialize random number generator
mt19937 rng(time(0));

// build shuffled deck of card effects
deque<int> build_deck(const vector<string>& choices) {
    vector<int> numbers;
    for (const auto& square : choices) {
        numbers.push_back(square_numbers[square]);
    }
    shuffle(numbers.begin(), numbers.end(), rng);
    return deque<int>(numbers.begin(), numbers.end());
}

// initialize transition decks
map<int, deque<int>> transitions;

// handle special square transitions
int transition(int square_number) {
    while (transitions.count(square_number)) {
        auto& deck = transitions[square_number];
        int new_square = deck.front();
        deck.pop_front();
        deck.push_back(new_square);

        if (square_number == new_square) break;
        square_number = new_square;
    }
    return square_number;
}

// simulate dice roll and movement
int move(int current_pos, int die_size = 6) {
    uniform_int_distribution<int> dist(1, die_size);
    int roll = dist(rng) + dist(rng);
    int new_pos = (current_pos + roll) % num_squares;
    return transition(new_pos);
}

// main simulation function
void simulate(int iterations = 2000000, int die_size = 4) {
    vector<int> counts(num_squares, 0);
    int current_pos = 0;

    for (int i = 0; i < iterations; ++i) {
        current_pos = move(current_pos, die_size);
        counts[current_pos]++;
    }

    // collect and sort results
    vector<pair<int, int>> results;
    for (int i = 0; i < num_squares; ++i) {
        results.emplace_back(-counts[i], i);  // negative for descending sort
    }

    sort(results.begin(), results.end());

    // output top 3 squares
    cout << "most visited squares: ";
    for (int i = 0; i < 3; ++i) {
        cout << (results[i].second < 10 ? "0" : "") << results[i].second;
    }
    cout << endl;
}

int main() {
    // initialize square number mapping
    for (int i = 0; i < num_squares; ++i) {
        square_numbers[squares[i]] = i;
    }

    // set up transition decks
    transitions[square_numbers["G2J"]] = build_deck({"JAIL"});
    transitions[square_numbers["CH1"]] = build_deck({"CH1", "CH1", "CH1", "CH1", "CH1", "CH1",
                                                     "GO", "JAIL", "C1", "E3", "H2", "R1", "R2", "R2", "U1", "T1"});
    // ... similar initialization for other decks ...

    // run simulation
    simulate();
    return 0;
}