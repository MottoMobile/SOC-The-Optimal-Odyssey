#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef long long ll;
typedef pair<ll, int> pli;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int,ll>>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
    }

    // count[v] = how many times v has been popped
    vector<int> count(n + 1, 0);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    pq.push({0, 1});

    while (!pq.empty()) {
        auto [cost, u] = pq.top(); pq.pop();

        count[u]++;

        if (u == n) {
            cout << cost << '\n';
            if (count[n] == k) break;
        }

        if (count[u] > k) continue;

        for (auto [v, w] : adj[u]) {
            if (count[v] < k)
                pq.push({cost + w, v});
        }
    }

    return 0;
}
