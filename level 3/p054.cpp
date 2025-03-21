#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// convert the card character to its integer value
int cardValue(char c) {
    if (c == 'T') return 10;
    if (c == 'J') return 11;
    if (c == 'Q') return 12;
    if (c == 'K') return 13;
    if (c == 'A') return 14;
    return c - '0';
}

// struct to store the evaluation (ranking) of a poker hand
struct HandValue {
    int rank;                 // higher value indicates a better hand; e.g., 10 for royal flush, 1 for high card
    vector<int> tiebreakers;  // values for tie-breaking in descending order
};

// function that evaluates a hand (vector of 5 cards) and returns its ranking and tiebreakers
HandValue evaluateHand(const vector<string> &cards) {
    vector<int> values;
    vector<char> suits;
    for (auto &card : cards) {
        values.push_back(cardValue(card[0]));
        suits.push_back(card[1]);
    }
    sort(values.begin(), values.end());

    // check if all cards have the same suit (flush)
    bool flush = true;
    for (size_t i = 1; i < suits.size(); i++) {
        if (suits[i] != suits[0]) {
            flush = false;
            break;
        }
    }

    // check if the values are consecutive (straight)
    bool straight = true;
    for (int i = 0; i < 4; i++) {
        if (values[i + 1] - values[i] != 1) {
            straight = false;
            break;
        }
    }
    // special case: a,2,3,4,5 (ace low)
    if (!straight && values[0] == 2 && values[1] == 3 && values[2] == 4 &&
        values[3] == 5 && values[4] == 14) {
        straight = true;
        // adjust the ace to value 1 for tie-breaking purposes
        values[4] = 1;
        sort(values.begin(), values.end());
    }

    // count the frequency of each card value
    map<int, int> freq;
    for (auto v : values)
        freq[v]++;

    // create a vector of pairs (frequency, value) for sorting
    vector<pair<int, int>> freqPairs;
    for (auto &p : freq) {
        freqPairs.push_back({p.second, p.first});
    }
    // sort by frequency (descending) and by value (descending) in case of tie
    sort(freqPairs.begin(), freqPairs.end(), [](const pair<int, int> &a, const pair<int, int> &b) {
        if (a.first == b.first)
            return a.second > b.second;
        return a.first > b.first;
    });

    HandValue hv;

    // assign the hand ranking and set tie-breakers
    if (straight && flush) {
        // if straight flush, check if it is a royal flush (10 to ace)
        if (*max_element(values.begin(), values.end()) == 14 && *min_element(values.begin(), values.end()) == 10)
            hv.rank = 10;  // royal flush
        else
            hv.rank = 9;  // straight flush
        hv.tiebreakers.push_back(*max_element(values.begin(), values.end()));
    } else if (freqPairs[0].first == 4) {
        hv.rank = 8;  // four of a kind
        hv.tiebreakers.push_back(freqPairs[0].second);
        for (auto &p : freqPairs) {
            if (p.first == 1) {
                hv.tiebreakers.push_back(p.second);
                break;
            }
        }
    } else if (freqPairs[0].first == 3 && freqPairs[1].first == 2) {
        hv.rank = 7;                                    // full house
        hv.tiebreakers.push_back(freqPairs[0].second);  // three of a kind value
        hv.tiebreakers.push_back(freqPairs[1].second);  // pair value
    } else if (flush) {
        hv.rank = 6;  // flush
        vector<int> sorted = values;
        sort(sorted.begin(), sorted.end(), greater<int>());
        hv.tiebreakers = sorted;
    } else if (straight) {
        hv.rank = 5;  // straight
        hv.tiebreakers.push_back(*max_element(values.begin(), values.end()));
    } else if (freqPairs[0].first == 3) {
        hv.rank = 4;  // three of a kind
        hv.tiebreakers.push_back(freqPairs[0].second);
        vector<int> kickers;
        for (auto &p : freqPairs)
            if (p.first == 1)
                kickers.push_back(p.second);
        sort(kickers.begin(), kickers.end(), greater<int>());
        hv.tiebreakers.insert(hv.tiebreakers.end(), kickers.begin(), kickers.end());
    } else if (freqPairs[0].first == 2 && freqPairs.size() >= 3 && freqPairs[1].first == 2) {
        hv.rank = 3;                                    // two pairs
        hv.tiebreakers.push_back(freqPairs[0].second);  // higher pair
        hv.tiebreakers.push_back(freqPairs[1].second);  // lower pair
        for (auto &p : freqPairs) {
            if (p.first == 1) {
                hv.tiebreakers.push_back(p.second);  // kicker
                break;
            }
        }
    } else if (freqPairs[0].first == 2) {
        hv.rank = 2;  // one pair
        hv.tiebreakers.push_back(freqPairs[0].second);
        vector<int> kickers;
        for (auto &p : freqPairs)
            if (p.first == 1)
                kickers.push_back(p.second);
        sort(kickers.begin(), kickers.end(), greater<int>());
        hv.tiebreakers.insert(hv.tiebreakers.end(), kickers.begin(), kickers.end());
    } else {
        hv.rank = 1;  // high card
        vector<int> sorted = values;
        sort(sorted.begin(), sorted.end(), greater<int>());
        hv.tiebreakers = sorted;
    }

    return hv;
}

// function to compare two evaluated hands; returns true if player 1 wins
bool player1Wins(const vector<string> &hand1, const vector<string> &hand2) {
    HandValue hv1 = evaluateHand(hand1);
    HandValue hv2 = evaluateHand(hand2);

    if (hv1.rank != hv2.rank)
        return hv1.rank > hv2.rank;
    else {
        // if the ranks are equal, compare tiebreakers one by one
        for (size_t i = 0; i < min(hv1.tiebreakers.size(), hv2.tiebreakers.size()); i++) {
            if (hv1.tiebreakers[i] != hv2.tiebreakers[i])
                return hv1.tiebreakers[i] > hv2.tiebreakers[i];
        }
    }
    return false;  // in case of a tie (should not happen per problem statement)
}

int main() {
    ifstream infile("poker.txt");
    if (!infile) {
        cerr << "could not open file poker.txt" << endl;
        return 1;
    }

    string line;
    int player1WinCount = 0;

    while (getline(infile, line)) {
        if (line.empty())
            continue;

        istringstream iss(line);
        vector<string> cards;
        string card;
        while (iss >> card)
            cards.push_back(card);

        // first 5 cards belong to player 1, next 5 to player 2
        vector<string> hand1(cards.begin(), cards.begin() + 5);
        vector<string> hand2(cards.begin() + 5, cards.end());

        if (player1Wins(hand1, hand2))
            player1WinCount++;
    }

    cout << "player 1 wins " << player1WinCount << " hands." << endl;
    return 0;
}
