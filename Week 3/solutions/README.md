# Week 3: A* Algorithm and Heuristic Search

---

## 1. The Problem with Dijkstra

Dijkstra gives us the optimal shortest path, but it is **uninformed**. It expands outward in all directions with no sense of where the goal actually is. On a large graph where you only want the path from source *s* to a single target *t*, Dijkstra does a lot of wasted work exploring nodes in directions that have nothing to do with *t*.

The fix: give the algorithm *information* about the goal. This is the shift from **uninformed search** to **informed (heuristic) search**.

---

## 2. The Search Family: BFS to Dijkstra to Greedy Best-First to A*

All four algorithms share the same loop skeleton: pick a node from a frontier, expand its neighbors. What differs is **the priority used to pick the next node**.

| Algorithm | Priority Function | What it optimises |
| --- | --- | --- |
| BFS | Level (FIFO) | Fewest hops (unweighted) |
| Dijkstra | g(n), actual cost from start | True shortest path (weighted) |
| Greedy Best-First | h(n), estimated cost to goal | Speed toward goal (not optimal) |
| **A\*** | f(n) = g(n) + h(n) | Both: optimal *and* goal-directed |

**g(n)** is the cost accumulated so far. **h(n)** is the heuristic, your estimate of remaining distance to *t*. Dijkstra is exactly A* with h = 0.

---

## 3. The Heuristic Function h

h maps each node to an estimate of the remaining cost to reach the target *t*.

For this assignment (grid graphs with 4-directional movement), two natural choices are:

**Manhattan distance** (exact fit for 4-connected grids):

$$h_{\text{manhattan}}(n) = |x_n - x_t| + |y_n - y_t|$$

**Euclidean distance** (straight-line):

$$h_{\text{euclidean}}(n) = \sqrt{(x_n - x_t)^2 + (y_n - y_t)^2}$$

The heuristic is the only thing separating A* from Dijkstra. A bad or absent heuristic degrades A* back to Dijkstra. A good one makes it dramatically faster.

---

## 4. Admissibility: The Correctness Condition

**Definition:** h is *admissible* if for every node *n*:

$$0 \le h(n) \le h^*(n)$$

where h*(n) is the true shortest-path distance from *n* to the goal.

In plain terms: h must **never overestimate**. It can be conservative (underestimate), but it cannot be optimistic about a path that is actually expensive.

**Why it matters:** If h overestimates, A* can prematurely commit to a path that looks good by the heuristic but is actually suboptimal. With an admissible h, optimality is guaranteed.

**Are our heuristics admissible on a 4-connected grid?**
- Euclidean: yes. Straight-line distance is always ≤ actual grid path distance.
- Manhattan: yes. On a 4-connected grid (up/down/left/right only), the Manhattan distance is exactly the minimum number of steps ignoring obstacles. With obstacles in the way, the true cost can only be ≥ Manhattan, so it never overestimates.

Manhattan is a **tighter** admissible heuristic (closer to h*) than Euclidean on a 4-connected grid, which is why it typically explores fewer nodes.

---

## 5. Consistency (Monotonicity): The Efficiency Condition

**Definition:** h is *consistent* if for every edge (n, n') with cost c(n, n'):

$$h(n) \le c(n, n') + h(n')$$

This is the **triangle inequality** for the heuristic: the estimated cost from *n* cannot exceed the actual step to *n'* plus the estimated cost from *n'*.

Consistency implies admissibility (the converse is not generally true).

**Why it matters:** A consistent heuristic guarantees that once a node is popped from the priority queue, its g-value is already optimal, so no node ever needs to re-enter the open set. This makes A* behave structurally like Dijkstra: each node is processed at most once.

With only admissibility (not consistency), a node *can* re-enter the open set with a better g-value. The algorithm stays correct but requires more bookkeeping.

Both Manhattan and Euclidean are consistent on grids.

---

## 6. The A* Algorithm

```
A*(graph, start s, goal t, heuristic h):
    open_set = priority queue, keyed by f = g + h
    g[v] = inf  for all v
    g[s] = 0
    came_from[s] = None
    open_set.insert(s, f = g[s] + h(s))

    while open_set is not empty:
        current = open_set.pop_min()

        if current == t:
            return reconstruct_path(came_from, t)

        for each neighbor n of current with edge cost c:
            tentative_g = g[current] + c
            if tentative_g < g[n]:
                g[n] = tentative_g
                came_from[n] = current
                f = g[n] + h(n)
                open_set.insert_or_update(n, f)

    return NO_PATH
```

Path reconstruction is identical to Dijkstra: follow `came_from` backwards from *t* to *s*.

**What `nodes_explored` means in this assignment:** count each time `current = open_set.pop_min()` executes. This directly measures search work and is machine-independent, unlike raw time.

---

## 7. Optimality Proof (Sketch)

**Theorem:** If h is admissible, A* finds the optimal path.

**Proof by contradiction:** Suppose A* terminates with a suboptimal path of cost l' > l*. Let v_0, v_1, ..., v_k = t be the optimal path of cost l*. Since A* did not follow this path, some node v_i on it must still be sitting in the open set when *t* was popped.

The priority of v_i is g(v_i) + h(v_i). By admissibility, h(v_i) ≤ cost from v_i to *t* along the optimal path. So:

$$f(v_i) = g(v_i) + h(v_i) \le l^*$$

But A* popped *t* with f(t) = g(t) = l', and the priority queue always pops the minimum. So l' ≤ f(v_i) ≤ l*, which contradicts l' > l*. ∎

---

## 8. Connection to Dijkstra

| | Dijkstra | A* (consistent h) | A* (admissible only) |
| --- | --- | --- | --- |
| Priority | g(n) | g(n) + h(n) | g(n) + h(n) |
| Each node processed | once | once | possibly multiple times |
| Finds shortest path | always | yes | yes |
| Goal-directed | no | yes | yes |

When h = 0, A* reduces exactly to Dijkstra. As h grows closer to h*, A* explores fewer and fewer nodes. If h = h* exactly, A* explores only the nodes on the optimal path, nothing else.

---

## 9. Heuristic Comparison on 4-Connected Grids

**Why Manhattan dominates Euclidean here:**

On a 4-connected grid you can only move in 4 directions. The shortest possible path (no obstacles) takes exactly |dx| + |dy| steps. Manhattan distance captures this precisely and is thus a *tighter* lower bound than Euclidean.

Euclidean assumes you can travel diagonally, so it underestimates more aggressively. More nodes end up passing the f(n) ≤ f* threshold and get explored. Manhattan "knows" the actual movement model and prunes harder.

Expected ranking on this assignment's grids:

$$\text{nodes explored: Dijkstra} > \text{A* euclidean} > \text{A* manhattan}$$

All three produce the **same path length** since all paths are optimal. The difference is purely in search effort.

---

## 10. TSP Connection

This week is the foundation for Week 6. In TSP, A* can compute exact inter-city distances on a road network rather than using straight-line Euclidean approximations. The heuristic used there is MST-based: the cost of a minimum spanning tree over the unvisited cities is an admissible lower bound on the remaining tour cost. Same principle as here: never overestimate, prune aggressively.

---

## Complexity

| | Time | Space |
| --- | --- | --- |
| A* (worst case) | O((V + E) log V), same as Dijkstra | O(V) for open set + g array |
| A* (best case, h = h*) | O(d log d) where d is path length | O(d) |

Worst case matches Dijkstra because with h = 0 or a very poor heuristic, A* is Dijkstra. The heuristic improves practical performance but does not change the asymptotic worst case.
