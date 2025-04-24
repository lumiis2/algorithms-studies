#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second
#define pb push_back

using namespace std;

const int INF = 1e8+10;
const int MAX = 50000 + 10;
int n;
vector<int> v;

int main(){ _ 

    cin >> n;
    for (int i = 0; i < n; i++){
        int a; cin >> a;
        v.pb(a);
    }

    int x = -100000, bef = -100000;

    for(int i = 0; i < n; i++){ // percorrendo todas as salas
        if(bef < 0) bef = v[i]; // se o valor anterior for negativo, agora ele eh o prox
        else bef += v[i]; // se nao, ele eh somado ao prox
        x = max(x, bef); // vai ser o max entre o atual e o anterior/soma de anteriores
    }
    cout << x << endl;


    return 0;
}
