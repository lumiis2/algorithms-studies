#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second
#define pb push_back

using namespace std;

const int MAX = 1e5+10;
int n, c, t;
int v[MAX];

bool possible(long long seg){
    int comp = 1;
    int qntd = t*seg;
    for(int i = 0; i < n; i++){
        if(qntd >= v[i]) qntd -= v[i];
        else{
            comp ++;
            qntd = t*seg;
            i--;
        }
        if(comp > c) return 0;
    }
    return 1;
    
}

int main(){ _

    cin >> n >> c >> t;
    for(int i = 0; i< n; i++) cin >> v[i];

    int L = 0, R = MAX;
    while(L<R){
        int m = (L+R)/2;
        if(!possible(m)) L= m+1;
        else R = m;
    }
    cout << L << endl;

    return 0;
}