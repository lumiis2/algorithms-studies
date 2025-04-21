/*
Given an Alphabet E, a text T[1...n] and a pattern P[1...m]
Deterministic Finite Automaton (DFA) String Matching Algorithm
*/

#include <bits/stdc++.h>
using namespace std;

map<int, map<char, int>> transition(string& pattern, set<char>& alphabet, int m) { // O(m^3 x |E|)
    map<int, map<char, int>> delta; // transition map: state -> (char -> next state)
    for (int q = 0; q <= m; q++) { // q = current state (prefix of pattern matched so far)
        for (char a : alphabet) { // for each character in the alphabet
            string prefix = pattern.substr(0, q) + a; // simulate reading char 'a' at state q
            int k = min(m, q + 1); // k = max possible new state (size of matched prefix)
            while (k > 0 && prefix.substr(prefix.size() - k) != pattern.substr(0, k)) k--; // find longest prefix == suffix
            delta[q][a] = k; // set transition from state q with input a to state k
        }
    }
    return delta; // return transition table
}

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    if(m == 0 || n < m) return 0;

    set<char> alphabet(text.begin(), text.end());

    map<int, map<char, int>> delta = transition(pattern, alphabet, m);

    int q = 0;
    for (int i = 0; i < n; i++) {
        char c = text[i];
        if (delta[q].count(c))
            q = delta[q][c];
        else
            q = 0;

        if (q == m) {
            cout << "Pattern occurs with shift " << i - m + 1 << endl;
        }
    }

    return 0;
}
