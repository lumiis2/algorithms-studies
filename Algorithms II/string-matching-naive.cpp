/*
Given an Alphabet E, a text T[1...n] and a pattern P[1...m]
Naive String Matching Algorithm
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    for (int i = 0; i <= n - m; i++) {
        bool match = true;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            cout << "Pattern occurs with shift " << i << endl;
        }
    }

    return 0;
}

