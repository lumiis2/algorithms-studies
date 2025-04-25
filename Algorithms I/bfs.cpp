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

// BFS traversal
void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << ' ';

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << '\n';
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

    bfs(0); // or any other starting vertex

    return 0;
}
