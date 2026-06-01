# 2. Greedy Strategies in Graphs

## Greedy Strategies in Graphs

A **greedy algorithm** makes the locally optimal choice at each step, hoping it leads to a globally optimal solution.

In graph problems, this means — at every decision point, pick the best available option **right now**, without looking ahead.

Dijkstra is the perfect example — at every step, pick the unvisited node with the smallest current distance. That's a greedy choice.

---

## Local vs Global Optimum

A **local optimum** is the best choice at a given step.
A **global optimum** is the best solution overall.

The danger with greedy algorithms — a locally optimal choice doesn't always lead to a globally optimal solution.

**Example where greedy works:**

```
S --1-- A --1-- E
 \             /
  4           /
   \         /
    B ---2--/
```

Greedy from S picks A (cost 1). Total S→A→E = 2, which is optimal.

**Example where greedy fails:**

```
S --1-- A --10-- E
 \               /
  3             /
   \           /
    B ---2----/
```

Greedy picks A (cost 1), total S→A→E = 11. But S→B→E = 5. Greedy failed.

> This is why **not every problem can be solved greedily** — you need to prove that the greedy choice is safe before using it.
> 

---

## Proving Greedy Choices Mathematically

There are two standard proof techniques:

### 1. Greedy Stays Ahead

Show that after every step, the greedy solution is at least as good as any other solution.

**Used for: Dijkstra's Algorithm**

**Claim:** When a node $u$ is popped from the PQ, `dist[u]` is final — no shorter path exists.

**Proof by contradiction:**

Assume when we pop $u$, there exists a shorter path $P$ we haven't found yet. That path must go through some unvisited node $v$ at some point. But $v$ is in the PQ with:

$dist[v] \geq dist[u]$

Otherwise $v$ would have been popped first. So any path through $v$ has cost at least $dist[v] \geq dist[u]$. Adding more non-negative edges after $v$ only increases the cost further. So $P$ can't be shorter. **Contradiction.**

> This breaks with negative edges — a negative edge after $v$ could make $P$ shorter, invalidating the argument. This is why Dijkstra fails on negative edges.
> 

---

### 2. Exchange Argument

Assume there's an optimal solution that differs from greedy. Show that you can swap the differing choice with the greedy choice without making things worse.

**Used for: Kruskal's and Prim's Algorithm**

**Claim:** The greedy choice (pick the cheapest edge) is always in some optimal solution.

**Proof structure:**

Take an optimal solution $O$ that differs from greedy solution $G$. Find the first edge $e$ where they differ — $G$ picked $e$, $O$ didn't.

Now take $O$ and swap in $e$, removing whatever edge $f$ it used instead. Show that:

$cost(O$ with $e) \leq cost(O$ with $f)$

Since $e$ was the greedy (cheapest) choice at that step:

$cost(e) \leq cost(f)$

So the swap doesn't make $O$ worse. Therefore the greedy choice is always safe.

---

## Summary

|  | Greedy Stays Ahead | Exchange Argument |
| --- | --- | --- |
| Strategy | Show greedy is never behind | Show greedy can replace optimal without loss |
| Used for | Dijkstra | Kruskal's, Prim's |
| Direction | Forward — step by step | Backward — start from optimal, morph to greedy |