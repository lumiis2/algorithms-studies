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

const int MAX = 1e5 + 10;
vector<int> adj[MAX];
bool visited[MAX];

bool is_cycle(int u){
    queue<int> q;
    q.push(u);
    visited[u] = true;
    bool iscycle = true;

    while(!q.empty()){
        int node = q.front(); q.pop();

        if(adj[node].size() != 2) iscycle = false;

        for(int v : adj[node]){
            if(!visited[v]){
                visited[v]= true;
                q.push(v);
            }
        }
    }
    return iscycle;
}

int main() { _
    int n, m;
    cin >> n >> m;

    for(int i = 0; i<m; i++){
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++){
        if(!visited[i]){
            if(is_cycle(i)) cnt++;
        }
    }

    cout << cnt << endl;
    return 0;
}
