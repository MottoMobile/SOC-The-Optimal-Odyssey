#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, m;
char grid[1001][1001];
int distA[1001][1001];
int distM[1001][1001];
pair<int,int> parent[1001][1001];
char dirChar[1001][1001];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
char dc[] = {'R', 'L', 'D', 'U'};

queue<pair<int,int>> monsterQ;
queue<pair<int,int>> playerQ;

void bfsMonsters() {
    // your logic
    while (!monsterQ.empty()) {
        auto [x, y] = monsterQ.front();
        monsterQ.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && distM[nx][ny] == -1) {
                distM[nx][ny] = distM[x][y] + 1;
                monsterQ.push({nx, ny});
            }
        }
    }
}

void bfsPlayer() {
    // your logic — only enqueue cells where distA < distM
    while (!playerQ.empty()) {
        auto [x, y] = playerQ.front();
        playerQ.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] != '#' && distA[nx][ny] == -1) {
                distA[nx][ny] = distA[x][y] + 1;
                parent[nx][ny] = {x, y};
                dirChar[nx][ny] = dc[i];
                if (distA[nx][ny] < distM[nx][ny] || distM[nx][ny] == -1) {
                    playerQ.push({nx, ny});
                }
            }
        }
    }
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> grid[i];

    fill(&distA[0][0], &distA[0][0] + 1001 * 1001, -1);
    fill(&distM[0][0], &distM[0][0] + 1001 * 1001, -1);
    fill(&parent[0][0], &parent[0][0] + 1001 * 1001, make_pair(-1, -1));

    // scan grid, find A and all M positions, push into respective queues
    int sx, sy;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                sx = i;
                sy = j;
                distA[i][j] = 0;
                playerQ.push({i, j});
            }
            if (grid[i][j] == 'M') {
                distM[i][j] = 0;
                monsterQ.push({i, j});
            }
        }

    bfsMonsters();
    bfsPlayer();

    // check all boundary cells for a reachable safe cell
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i == 0 || i == n-1 || j == 0 || j == m-1) && distA[i][j] != -1 && (distM[i][j] == -1 || distA[i][j] < distM[i][j])) {
                // found a safe exit, reconstruct path
                string path;
                int x = i, y = j;
                while (parent[x][y] != make_pair(-1, -1)) {
                    path += dirChar[x][y];
                    tie(x, y) = parent[x][y];
                }
                reverse(path.begin(), path.end());
                cout << "YES\n" << path.size() << "\n" << path << "\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
}