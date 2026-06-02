#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const long long INF = 1e18;
int main() {
    int n, m;
    cin >> n >> m;
    
    // adjacency list: {neighbour, weight}
    vector<vector<pair<int,int>>> adj(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        // fill this
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }
    
    vector<long long> dist(n + 1, INF);
    dist[1] = 0;
    
    // {distance, node}
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, 1});
    vector <int> parent(n + 1, -1);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        // stale check — fill this
        if(d > dist[u])continue;
        
        for (auto [v, w] : adj[u]) {
            // relaxation — fill this
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    if (dist[n] == INF) {
        cout << -1 << endl;
    } else {
        vector<int> path;
        for (int v = n; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        
        for (int v : path) {
            cout << v << " ";
        }
        cout << endl;
    }
}
