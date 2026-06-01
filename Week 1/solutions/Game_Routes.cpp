#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long MOD = 1e9 + 7;

int n, m;
vector<int> adj[100001];
vector<int> radj[100001];
long long paths[100001];
bool visited[100001];
vector<int> order;

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v])
            dfs(v);
    order.push_back(u);
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
        if (!visited[i])
            dfs(i);

    reverse(order.begin(), order.end());

    paths[n] = 1;
    for (int i = order.size() - 1; i >= 0; i--) {
        int u = order[i];
        for (int v : adj[u]) {
            paths[u] = (paths[u] + paths[v]) % MOD;
        }
    }

    cout << paths[1] << "\n";

    return 0;
}