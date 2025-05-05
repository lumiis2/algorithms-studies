#include <bits/stdc++.h>
using namespace std;

// vector<int> prefix_function(string& pattern, int m) { // O(m)
//     vector<int> p(m);
//     p[0] = 0;
//     int k = 0;
//     for(int q = 1; q < m; q++) {
//         while(k > 0 && pattern[k] != pattern[q])
//             k = p[k-1];
//         if(pattern[k] == pattern[q])
//             k++;
//         p[q] = k;
//     }
//     return p;
// }


// otimization
vector<int> prefix_function(string& pattern, int m) { // O(m)
    vector<int> p(m);
    p[0] = 0;
    int k = 0;
    int i = 1;
    while(i < m) {
        if(pattern[i] == pattern[k]){
            k++;
            p[i] = k;
            i++;
        }
        else{
            if(k != 0) {
                k = p[k-1];
            }
            else{
                p[i] = 0;
                i++;
            }
        }
    }
    return p;
}

void print_alignment(const string& text, const string& pattern, int pos_in_text, int matched) {
    // Print the text
    cout << text << endl;
    
    // Print spaces to align the pattern
    for (int i = 0; i < pos_in_text - matched + 1; i++) 
        cout << " ";
    
    // Print the pattern with matched prefix highlighted
    for (int i = 0; i < pattern.size(); i++) {
        if (i < matched) {
            cout << pattern[i]; // matched part
        } else {
            cout << pattern[i]; // not matched yet
        }
    }
    cout << endl << endl;
}

int main() {
    string text, pattern;

    getline(cin, text);
    getline(cin, pattern);

    int n = text.size();
    int m = pattern.size();

    if(m == 0 || n < m) return 0;

    vector<int> pi = prefix_function(pattern, m);

    cout << "Prefix function: ";
    for(int i = 0; i < m; i++) 
        cout << pi[i] << " ";  
    cout << endl << endl;  

    int q  = 0;
    bool found = false;

    for (int i = 0; i < n; i++) {
        while(q > 0 && pattern[q] != text[i])
            q = pi[q-1];

        if(pattern[q] == text[i])
            q++;

        // Visual print
        print_alignment(text, pattern, i, q);

        if (q == m) {
            cout << "Pattern occurs with shift " << i - m + 1 << "!" << endl << endl;
            found = true;
            q = pi[q-1];  
        }
    }

    if (!found) {
        cout << "Pattern does not occur" << endl;
    }

    return 0;
}
