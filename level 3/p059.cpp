#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // open the cipher file
    ifstream infile("0059_cipher.txt");
    if (!infile) {
        cerr << "could not open file" << endl;
        return 1;
    }

    // read the entire file content (the file contains comma-separated numbers)
    string line;
    getline(infile, line);
    infile.close();

    // parse the numbers separated by commas into a vector
    vector<int> cipher;
    istringstream iss(line);
    string number;
    while (getline(iss, number, ',')) {
        cipher.push_back(stoi(number));
    }

    // try all keys (each key is three lowercase letters)
    for (char k1 = 'a'; k1 <= 'z'; k1++) {
        for (char k2 = 'a'; k2 <= 'z'; k2++) {
            for (char k3 = 'a'; k3 <= 'z'; k3++) {
                string decrypted;
                decrypted.reserve(cipher.size());

                // decrypt the cipher text using the cyclic key (k1, k2, k3)
                for (size_t i = 0; i < cipher.size(); i++) {
                    char key_char;
                    if (i % 3 == 0)
                        key_char = k1;
                    else if (i % 3 == 1)
                        key_char = k2;
                    else
                        key_char = k3;

                    char dec_char = static_cast<char>(cipher[i] ^ key_char);
                    // allow typical printable characters and newline (ascii 10)
                    if (!(dec_char == '\n' || (dec_char >= 32 && dec_char <= 126))) {
                        decrypted.clear();
                        break;
                    }
                    decrypted.push_back(dec_char);
                }

                // if the decrypted text is empty, this key is invalid; try the next one
                if (decrypted.empty())
                    continue;

                // check if the decrypted text contains common english words, e.g. " the "
                if (decrypted.find(" the ") != string::npos) {
                    // compute the sum of ascii values in the decrypted text
                    long long sum = 0;
                    for (char ch : decrypted)
                        sum += ch;

                    // output the key and the sum of ascii values
                    cout << "key: " << k1 << k2 << k3 << "\n";
                    cout << "sum of ascii values: " << sum << "\n";
                    // output the decrypted text (optional)
                    cout << "decrypted text:\n"
                         << decrypted << "\n";
                    return 0;
                }
            }
        }
    }

    return 0;
}
