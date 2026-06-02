#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> parent, rnk;

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);  // path compression
    return parent[x];
}

void unite(int x, int y) {
    x = find(x); y = find(y);         // find roots of both
    if (x == y) return;                // already in same component
    if (rnk[x] < rnk[y]) swap(x, y); // make x the larger tree
    parent[y] = x;                     // attach smaller under larger
    if (rnk[x] == rnk[y]) rnk[x]++;  // update rank if equal
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector <tuple<int, int, int>> edges(m);
    for(auto& [w, a, b] : edges)
    {
        cin >> a >> b >> w;
    }

    sort(edges.begin(), edges.end()); // sort by weight 
    parent.resize(n+1);
    rnk.resize(n+1, 0);

    for(int i = 1; i <= n; i++)
        parent[i] = i; // initialize union-find

    long long int total_cost = 0;
    for(auto& [w, a, b] : edges)
    {
        if(find(a) != find(b)) // if a and b are in different components
        {
            unite(a, b); // unite the components
            total_cost += w; // add the cost of this edge
        }
    }
    for(int i = 1; i <= n; i++)
    {
        if(find(i) != find(1)) // check if all nodes are connected
        {
            cout << "IMPOSSIBLE" << endl; // if not, print IMPOSSIBLE
            return 0;
        }
    }
    cout << total_cost << endl; // print the total cost

    return 0;
}
