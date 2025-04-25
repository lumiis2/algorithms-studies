#include <bits/stdc++.h>
#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define f first
#define s second
#define pb push_back

using namespace std;

const int MAX = 1e5 + 10;

int n, m;
vector<int> adj[MAX];
bool visited[MAX];

// DFS traversal
void dfs(int u) {
    visited[u] = true;
    cout << u+1 << ' ';

    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main(){ _
    cin >> n >> m;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--; // convert to 0-based indexing
        adj[u].pb(v);
        adj[v].pb(u); // if the graph is directed, remove this line
    }

    dfs(0); // or any other starting vertex

    return 0;
}
