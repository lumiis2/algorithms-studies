/*
um componente vai ser um componente conxeo e ciclico se:
rodando uam bfs/dfs for visto que ele eh conexo
se cada vertice tem grau pelo menos 2
*/

#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second
#define pb push_back

using namespace std;

const int MAX = 200 * 1000 + 11;

int n, m;
vector<int> adj[MAX];
vector<int> comp;
bool visited[MAX];
int deg[MAX]; // grau de cada vertice


void dfs(int v){
    visited[v] = true;
    comp.pb(v);

    for(auto e : adj[v]){
        if(!visited[e]) dfs(e);
    }
}

int main() { _

    cin >> n >> m;

    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[v]++;
        deg[u]++;
    }

    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(!visited[i]){
            comp.clear();
            dfs(i);
            bool cycle = true;
            for(auto v : comp) cycle &= deg[v] == 2;
            if(cycle) cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}
