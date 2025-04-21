/*
Given an Alphabet E, a text T[1...n] and a pattern P[1...m]
Knuth-Morris-Pratt (KMP) String Matching Algorithm
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_function(string& pattern, int m) { // O(m)
    vector<int> p(m);
    p[0] = 0;
    int k = 0;
    for(int q = 1; q < m; q++){
        while(k > 0 && pattern[k+1] != pattern[q]) k = p[k];
        if(pattern[k+1] == pattern[q]) k++;
        p[q] = k;
    }
    return p;
}

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    if(m == 0 || n < m) return 0;

    vector<int> pi = prefix_function(pattern, m);
    int q  = 0;

    for (int i = 1; i < n; i++) {
        while(q > 0 && pattern[q+1] != text[i]) q = pi[q];
        if (pattern[q+1] ==  text[i]) q++;
        if (q == m) {
            cout << "Pattern occurs with shift " << i - m + 1 << endl;
            q = pi[q-1];
        }
    }
    // O(m+n)

    return 0;
}
