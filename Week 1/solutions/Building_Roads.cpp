#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int n, m;
vector<int> adj[100001];
bool visited[100001];
vector<int> representatives;

void dfs(int start) {
    stack<int> st;
    st.push(start);
    visited[start] = true;
    while (!st.empty()) {
        int u = st.top(); st.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                st.push(v);
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            representatives.push_back(i);
            dfs(i);
        }
    }

    cout << representatives.size() - 1 << "\n";
    for (int i = 0; i < (int)representatives.size() - 1; i++) {
        cout << representatives[i] << " " << representatives[i + 1] << "\n";
    }
    return 0;
}