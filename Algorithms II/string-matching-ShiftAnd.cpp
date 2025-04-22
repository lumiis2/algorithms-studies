/*
Given an Alphabet E, a text T[1...n] and a pattern P[1...m]
Shift-And String Matching Algorithm
*/

#include <bits/stdc++.h>
using namespace std;

int main(){

    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    if(m == 0 || n < m || m > 64) return 0;

    unordered_map<char, uint64_t> mask;
    for(char c : text) mask [c] = 0;
    for(int i = 0; i < m; i++) mask[pattern[i]] |= (1ULL << i);

    uint64_t state = 0;
    uint64_t match_bit = 1ULL << (m - 1);
    vector<int> positions;

    for(int i = 0; i<n; i++){
        state = ((state << 1)| 1) & mask[text[i]];
        if(state & match_bit){
            positions.push_back(i-m+1);
        }
    }

    for (int pos : positions) {
            cout << "Pattern occurs with shift " << pos << endl;
    }


    return 0;
}