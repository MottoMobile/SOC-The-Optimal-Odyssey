# Week 1 — Graphs, BFS & DFS

---

## 1. Introduction to Graphs

A **graph** is a pair $G = (V, E)$ where:

- $V$ is a set of **vertices** (also called nodes)
- $E$ is a set of **edges** — connections between pairs of vertices

### Directed vs Undirected

In an **undirected** graph, an edge $(u, v)$ goes both ways. In a **directed** graph (digraph), $(u, v)$ goes only from $u$ to $v$.

TSP is typically defined on a **complete** directed (or undirected) graph — every city is connected to every other.

### Weighted vs Unweighted

In a **weighted** graph, each edge carries a number — a cost, distance, or time. The length of a path is the sum of its edge weights. TSP lives in this version: you want the minimum-weight tour.

### Degree

The **degree** of a node is how many edges touch it. In a directed graph this splits into:
- **Indegree** — edges coming in
- **Outdegree** — edges going out

> **Note:** The sum of all degrees always equals $2|E|$, since every edge contributes to exactly two nodes (Handshaking Lemma).

### Connected vs Disconnected

A graph is **connected** if there is a path between every pair of nodes. Otherwise it's **disconnected**, and it decomposes into **connected components** — maximal subgraphs that are internally connected. This matters immediately: problems like Counting Rooms and Building Roads are literally asking you to count or bridge components.

### Paths and Cycles

A **path** is a sequence of nodes connected by edges. It's **simple** if no node repeats.

A **cycle** is a closed path — start and end at the same node. TSP is asking for the minimum-weight **Hamiltonian cycle**: a cycle that visits every node exactly once.

---

## 2. Graph Representations

### Adjacency Matrix

A 2D array `adj[n][n]`. Entry `adj[i][j] = 1` (or the edge weight) if there's an edge from $i$ to $j$, else 0.

| Operation | Complexity |
|---|---|
| Space | $O(n^2)$ — always, regardless of edge count |
| Edge existence check `adj[i][j]` | $O(1)$ |
| Iterate all neighbors of node $i$ | $O(n)$ — must scan entire row |

### Adjacency List

An array of vectors. `adj[i]` stores exactly the neighbors of node $i$.

```cpp
vector<int> adj[N];              // unweighted
vector<pair<int,int>> adj[N];    // weighted: {neighbor, weight}
```

| Operation | Complexity |
|---|---|
| Space | $O(n + m)$ where $m$ = number of edges |
| Edge existence check between $i$ and $j$ | $O(\deg(i))$ — scan the list |
| Iterate all neighbors of node $i$ | $O(\deg(i))$ — only actual neighbors |

### Edge List

A flat list of tuples $(u, v, w)$. Simple to sort by weight. Used directly in **Kruskal's algorithm** (Week 2).

```cpp
vector<tuple<int,int,int>> edges;  // {weight, u, v}
```

### When to Use Which

| Situation | Use |
|---|---|
| $n$ is small, graph is dense ($m \sim n^2$) | Matrix |
| Need $O(1)$ edge lookup | Matrix |
| Need matrix algebra (e.g. Floyd-Warshall) | Matrix |
| $n$ or $m$ is large, graph is sparse | List |
| Running BFS, DFS, or any traversal | List |
| Need to sort edges by weight (Kruskal's) | Edge list |

---

## 3. BFS — Breadth First Search

BFS explores the graph **level by level** from a source node. Uses a **queue** (FIFO).

BFS computes the **geodesic distance** from the source — the minimum number of edges to every reachable node. This is the exact shortest path in an *unweighted* graph.

### Algorithm

```cpp
BFS(G, s):
  mark s as visited
  enqueue s
  while queue is not empty:
    u = dequeue()
    for each neighbour v of u:
      if v not visited:
        mark v as visited
        distance[v] = distance[u] + 1
        parent[v] = u
        enqueue v
```

The `parent[]` array lets you reconstruct the shortest path by backtracking from the target to the source.

**Invariant:** BFS maintains $d[v] \leq d[u] + 1$ for all edges $(u, v)$, with equality when $v$ is discovered from $u$.

### Bipartiteness Check (2-Coloring)

BFS can check if a graph is **bipartite**: assign alternating colors (0/1) as you traverse. If you ever try to assign a color to a node that already has the same color as its neighbor — the graph is not bipartite (it has an odd cycle).

```cpp
// color[] initialized to -1
color[s] = 0;
enqueue s;
while queue not empty:
    u = dequeue()
    for each neighbour v of u:
        if color[v] == -1:
            color[v] = 1 - color[u]
            enqueue v
        else if color[v] == color[u]:
            // NOT bipartite
```

This is directly what Building Teams requires.

---

## 4. DFS — Depth First Search

DFS goes as deep as possible along one path before backtracking. Uses **recursion** (implicit call stack) or an **explicit stack** (LIFO).

### Recursive DFS

```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    // preorder: process u on entry
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
    // postorder: process u on exit
}
```

- **Preorder** (on entry): record discovery time
- **Postorder** (on exit): record finish time — reversing finish times gives a **topological order**

### Iterative DFS

```cpp
void dfs_iterative(int s, vector<vector<int>>& adj) {
    stack<int> st;
    vector<bool> visited(n, false);
    st.push(s);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) st.push(v);
        }
    }
}
```

> **Caution:** The iterative version marks nodes as visited *on pop*, not on push. This means the same node can be pushed multiple times before being visited — hence the `if (visited[u]) continue` guard. Recursive DFS marks on entry, so it never re-enters. Push neighbors in reverse order if you want matching traversal order.

### DFS Tree and Edge Classification

Running DFS on a graph induces a **DFS tree**. Edges are classified as:

| Edge Type | Meaning |
|---|---|
| Tree Edge | Used to discover a new node |
| Back Edge | From a node to an **ancestor** in the DFS tree |
| Forward Edge | From a node to a **descendant** (directed graphs only) |
| Cross Edge | Between different DFS subtrees (directed graphs only) |

**Cycle detection:** A back edge $(u, v)$ where $v$ is already on the current call stack means there's a cycle.

In **undirected** graphs, only tree edges and back edges exist — no forward or cross edges.

---

## 5. Complexity

| | BFS | DFS |
|---|---|---|
| Time | $O(V + E)$ | $O(V + E)$ |
| Space | $O(V)$ — queue can hold an entire level | $O(V)$ — stack depth bounded by longest path |

Both visit every node and edge exactly once. The space difference matters in practice: BFS on a star graph enqueues $V-1$ nodes at once; DFS on a long chain recurses $V$ deep (watch for stack overflow on $n \sim 10^5$).

---

## 6. Applications

### BFS
- Shortest path in an unweighted graph
- Level-order traversal
- Bipartiteness / 2-coloring (Building Teams)
- Multi-source BFS — start with multiple sources in the queue simultaneously (Monsters problem: BFS from all monster positions at once)

### DFS
- Connected components (Counting Rooms)
- Cycle detection (Round Trip, Round Trip II)
- Topological sort — reverse of DFS finish times (Game Routes)
- Articulation points and bridges
- Strongly connected components (Tarjan's / Kosaraju's)
- Backtracking and exhaustive search
