/*
Given an Alphabet E, a text T[1...n] and a pattern P[1...m]
Horspool String Matching Algorithm
*/

#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> shift_table(string& pattern, int m) { // O(m)
    unordered_map<char, int> table;
    for(int i = 0; i < m-1; i++){
        table[pattern[i]] = m - 1 - i;
    }
    return table;
}

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    if(m == 0 || n < m) return 0;

    unordered_map<char, int> shift = shift_table(pattern, m);

    int i = m-1;
    while(i <= n-1) {
        int j = 0;
        while(j <= m-1 && pattern[m-1-j] == text[i-j]) j++;
        if(j == m) {
            cout << "Pattern occurs with shift " << i-m + 1 << endl;
        }
        i += shift.count(text[i]) ? shift[text[i]] : m;
    }

    return 0;
}


