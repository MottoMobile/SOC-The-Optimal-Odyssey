#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector <int> parent, rnk;

int find(int x)
{
    if (x!=parent[x])
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y)
{
    int rx = find(x), ry = find(y);
    if (rx==ry) return;
    if (rnk[rx] < rnk[ry])
    {        
        parent[rx] = ry;
    }
    else if (rnk[ry] < rnk[rx])
    {        
        parent[ry] = rx;
    }
    else
    {        
        parent[ry] = rx;
        rnk[rx]++;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector <pair<int, int>>  edges;
    parent.resize(n+1);
    rnk.resize(n+1, 0);
    edges.resize(m);    
    vector<int> size(n+1);
    for(int i=0; i<=n; i++)
    {
        size[i] = 1;
    }

    for(auto& [a, b]: edges)
    {
        cin >> a >> b;
    }

    for(int i=1; i<=n; i++)
    {
        parent[i] = i;
    }
    int total_components = n;
    int largest = 0;
    for(auto& [a, b]: edges)
    {
        
        if (find(a) != find(b))
        {
            total_components--;
        
        int rx = find(a), ry = find(b); 
        if(rnk[rx] < rnk[ry])
        {
            size[ry] += size[rx];
        }
        else
        {
            size[rx] += size[ry];
        }
        }
        unite(a, b);
        largest = max(largest, max(size[find(a)], size[find(b)])); 
        cout << total_components << " " << largest << endl;
    }
    return 0;
}
