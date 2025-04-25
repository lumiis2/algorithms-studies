/*
basicamente um vertex cover, mas que um vertice a apenas um vertice fique sem cobertura.
ideia:
seto todos so vertices como tendo um guarda 1
vou no vertuce de menor grau e seto seus vizinhos pra 0
o grafo dado pode ser desconexo e esse nao pdoe ser um problema

*/


#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second
#define pb push_back

using namespace std;

const int INF = 1e8+10;
const int MAX = 50000 + 10;

int n, m;

int main() {
    cin >> n >> m;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // escolha um vértice com menor grau
    int min_deg = n+1, chosen = 0;
    for (int i = 0; i < n; ++i) {
        if ((int)adj[i].size() < min_deg) {
            min_deg = adj[i].size();
            chosen = i;
        }
    }

    vector<int> has_police(n, 1);
    has_police[chosen] = 0;
    for (int v : adj[chosen]) has_police[v] = 0;

    for (int i = 0; i < n; ++i)
        cout << has_police[i] << " ";
    cout << "\n";

    return 0;
}