#include <iostream>
#include <vector>
#include <queue>

using namespace std;

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
    }
    
    vector<long long> dist(n + 1, 1e18);
    dist[1] = 0;
    
    // {distance, node}
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> pq;
    pq.push({0, 1});
    
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
                pq.push({dist[v], v});
            }
        }
    }
    
    for (int i = 1; i <= n; i++) cout << dist[i] << " \n"[i == n];
}
