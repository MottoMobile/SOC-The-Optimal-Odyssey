#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
char grid[1001][1001];
bool visited[1001][1001];
pair<int,int> parent[1001][1001];
char dirChar[1001][1001];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char dc[] = {'R', 'L', 'D', 'U'};

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    int sx, sy, ex, ey;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') { sx = i; sy = j; }
            if (grid[i][j] == 'B') { ex = i; ey = j; }
        }

    queue<pair<int,int>> q;
    q.push({sx, sy});
    visited[sx][sy] = true;
    parent[sx][sy] = {-1, -1};

    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        if (x == ex && y == ey) break;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m
                && !visited[nx][ny]
                && (grid[nx][ny] == '.' || grid[nx][ny] == 'B')) {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                dirChar[nx][ny] = dc[i];
                q.push({nx, ny});
            }
        }
    }

    if (!visited[ex][ey]) {
        cout << "NO\n";
        return 0;
    }

    string path = "";
    int cx = ex, cy = ey;
    while (cx != sx || cy != sy) {
        path += dirChar[cx][cy];
        auto [px, py] = parent[cx][cy];
        cx = px; cy = py;
    }
    reverse(path.begin(), path.end());

    cout << "YES\n" << path.size() << "\n" << path << "\n";
    return 0;
}