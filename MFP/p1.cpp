#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define f first
#define s second 
#define pb push_back

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> freq(m+2, 0); 
    
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }
    
    vector<int> b(m+2, 0);
    
    for (int k = m; k >= 1; k--) {
        b[k] = freq[k] + b[k+1];
    }
    
    for (int k = 1; k <= m; k++) {
        cout << b[k] << " ";
    }
    cout << endl;
    
    return 0;
}
