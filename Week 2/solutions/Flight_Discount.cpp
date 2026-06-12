#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

typedef long long ll;
typedef pair<ll, pair<int,int>> State; // {cost, {city, coupon_used}}

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

    // dist[city][coupon_used]
    vector<vector<ll>> dist(n + 1, vector<ll>(2, LLONG_MAX));
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[1][0] = 0;
    pq.push({0, {1, 0}});

    while (!pq.empty()) {
        auto [cost, state] = pq.top(); pq.pop();
        auto [u, used] = state;

        if (cost > dist[u][used]) continue;

        for (auto [v, w] : adj[u]) {
            // don't use coupon
            if (dist[u][used] + w < dist[v][used]) {
                dist[v][used] = dist[u][used] + w;
                pq.push({dist[v][used], {v, used}});
            }
            // use coupon (only if not used yet)
            if (used == 0 && dist[u][0] + w / 2 < dist[v][1]) {
                dist[v][1] = dist[u][0] + w / 2;
                pq.push({dist[v][1], {v, 1}});
            }
        }
    }

    cout << min(dist[n][0], dist[n][1]) << '\n';

    return 0;
}
