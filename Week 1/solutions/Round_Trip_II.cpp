#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> adj[100001];
int parent[100001];
bool visited[100001];
bool inStack[100001];
int cycleStart, cycleEnd;

void dfs(int u) {
    if (cycleStart != -1) return;
    visited[u] = true;
    inStack[u] = true;
    for (int v : adj[u]) {
        if (cycleStart != -1) return;
        if (!visited[v]) {
            parent[v] = u;
            dfs(v);
        } else if (inStack[v]) {
            cycleStart = v;
            cycleEnd = u;
            return;
        }
    }
    inStack[u] = false;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
    }

    fill(parent + 1, parent + n + 1, -1);
    cycleStart = -1;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs(i);
        if (cycleStart != -1) break;
    }

    if (cycleStart == -1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> cycle;
    cycle.push_back(cycleStart);
    for (int v = cycleEnd; v != cycleStart; v = parent[v])
        cycle.push_back(v);
    cycle.push_back(cycleStart);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << "\n";
    for (int v : cycle) cout << v << " ";
    cout << "\n";
    return 0;
}