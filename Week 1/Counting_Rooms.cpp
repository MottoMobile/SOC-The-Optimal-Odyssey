#include <iostream>
#include <stack>
using namespace std;

int n, m;
char grid[1001][1001];
bool visited[1001][1001];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int x, int y) {
    stack<pair<int,int>> st;
    st.push({x, y});
    visited[x][y] = true;
    while (!st.empty()) {
        auto [cx, cy] = st.top(); st.pop();
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && grid[nx][ny] == '.') {
                visited[nx][ny] = true;
                st.push({nx, ny});
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> grid[i];
    
    int rooms = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                dfs(i, j);
                rooms++;
            }
        }
    }
    cout << rooms << endl;
    return 0;
}