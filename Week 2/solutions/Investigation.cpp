#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

const ll INF = LLONG_MAX;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int,ll>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    vector<ll>  dist(n + 1, INF);
    vector<ll>  cnt(n + 1, 0);   // number of min-cost routes
    vector<int> minf(n + 1, 0);  // min flights on min-cost route
    vector<int> maxf(n + 1, 0);  // max flights on min-cost route

    priority_queue<pli, vector<pli>, greater<pli>> pq;

    dist[1] = 0;
    cnt[1]  = 1;
    minf[1] = 0;
    maxf[1] = 0;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();

        if (cost > dist[u]) continue;

        for (auto [v, w] : adj[u]) {
            ll new_cost = dist[u] + w;

            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                cnt[v]  = cnt[u];
                minf[v] = minf[u] + 1;
                maxf[v] = maxf[u] + 1;
                pq.push({dist[v], v});
            } else if (new_cost == dist[v]) {
                cnt[v]  = (cnt[v] + cnt[u]) % MOD;
                minf[v] = min(minf[v], minf[u] + 1);
                maxf[v] = max(maxf[v], maxf[u] + 1);
            }
        }
    }

    cout << dist[n] << ' ' << cnt[n] << ' ' << minf[n] << ' ' << maxf[n] << '\n';

    return 0;
}
