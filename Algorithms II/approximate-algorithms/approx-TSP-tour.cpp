#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <set>

using namespace std;

const double INF = 1e9;

struct Point {
    double x, y;
};

double dist(const Point& a, const Point& b) {
    return hypot(a.x - b.x, a.y - b.y);
}

vector<vector<double>> buildGraph(const vector<Point>& points) {
    int n = points.size();
    vector<vector<double>> graph(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = dist(points[i], points[j]);
    return graph;
}

vector<vector<int>> primMST(const vector<vector<double>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<double> key(n, INF);
    vector<int> parent(n, -1);
    key[0] = 0;

    for (int count = 0; count < n; count++) {
        double minKey = INF;
        int u = -1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && key[v] < minKey)
                minKey = key[v], u = v;

        visited[u] = true;
        for (int v = 0; v < n; v++)
            if (graph[u][v] < key[v] && !visited[v])
                key[v] = graph[u][v], parent[v] = u;
    }

    vector<vector<int>> mst(n);
    for (int i = 1; i < n; i++) {
        mst[i].push_back(parent[i]);
        mst[parent[i]].push_back(i);
    }
    return mst;
}

void dfs(int u, const vector<vector<int>>& tree, vector<bool>& visited, vector<int>& path) {
    visited[u] = true;
    path.push_back(u);
    for (int v : tree[u])
        if (!visited[v])
            dfs(v, tree, visited, path);
}

pair<vector<int>, double> twiceAroundTheTree(const vector<Point>& points) {
    auto graph = buildGraph(points);
    auto mst = primMST(graph);

    vector<bool> visited(points.size(), false);
    vector<int> dfsPath;
    dfs(0, mst, visited, dfsPath);

    vector<bool> visitedTour(points.size(), false);
    vector<int> tour;
    for (int v : dfsPath)
        if (!visitedTour[v])
            tour.push_back(v), visitedTour[v] = true;
    tour.push_back(tour[0]);

    double cost = 0;
    for (int i = 0; i < (int)tour.size() - 1; i++)
        cost += graph[tour[i]][tour[i + 1]];

    return {tour, cost};
}

int main() {
    vector<Point> points = {{0, 0}, {1, 3}, {4, 3}, {6, 1}, {3, 0}};

    auto [tour1, cost1] = twiceAroundTheTree(points);
    cout << "Twice Around the Tree: ";
    for (int v : tour1) cout << v << " ";
    cout << "\nCost: " << cost1 << "\n";
    
    return 0;
}