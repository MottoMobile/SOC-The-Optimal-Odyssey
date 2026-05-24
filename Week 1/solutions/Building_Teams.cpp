#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
vector<int> adj[100001];
int team[100001];

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    fill(team + 1, team + n + 1, -1);
    bool possible = true;

    for (int i = 1; i <= n; i++) {
        if (team[i] != -1) continue;
        queue<int> q;
        q.push(i);
        team[i] = 1;
        while (!q.empty() && possible) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (team[v] == -1) {
                    team[v] = 3 - team[u];
                    q.push(v);
                } else if (team[v] == team[u]) {
                    possible = false;
                }
            }
        }
    }

    if (!possible) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    for (int i = 1; i <= n; i++)
        cout << team[i] << " \n"[i == n];
    return 0;
}