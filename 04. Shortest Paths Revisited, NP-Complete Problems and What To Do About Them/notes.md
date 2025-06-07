# Bellman Ford Algorithm
&rarr; The Bellman-Ford algorithm is a fundamental single-source shortest path algorithm that can handle graphs with negative edge weights, unlike Dijkstra's algorithm.
**Problem Statement**
**Input:**  Directed graph G(V, E), edge lengths $c_e$ (possibly negative), source vertex s.
**Output:**  For every destination v ∈ V, compute the length of a shortest s-v path.
###  Running Time Analysis
**Time Complexity:**  O(mn) where m = |E|, n = |V|.
-   Outer loop: n-1 iterations.
-   Inner loops: O(m) work per iteration.
-   Each edge is examined once per iteration.
**Space Optimization:**  Only need current and previous iteration values, so space can be reduced to O(n).
### Applications
1.  **Internet Routing:**  Bellman-Ford enables distributed shortest-path computation.
2.  **Currency Arbitrage:**  Detect negative cycles in exchange rate graphs.
3.  **Preprocessing for Johnson's Algorithm:**  Used to reweight graphs for all-pairs shortest paths.

### Comparison with Dijkstra
|Aspect|Dijkstra|Bellman-Ford|
|--|--|--|
| Edge weights | Non-negative only | Can handle negative|
|Time complexity|O(m logn)|O(mn)|
|Distributed|No|Yes|
|Negative cycle detection|No|Yes|
---

# All pairs shortest path problem
**Problem Definition**
**Input:**  Directed graph G(V,E) with edge lengths ce (possibly negative).
**Output:**  For every ordered pair of vertices u,v ∈ V, compute the length of a shortest u-v path.
**Key Challenge:**  We need shortest paths between  **all pairs**  of vertices, not just from a single source.
## Floyd-Warshall Algorithm
&rarr; Floyd-Warshall algorithm is a fundamental dynamic programming solution for the  <u>All-Pairs Shortest Path (APSP)</u>  problem that elegantly handles negative edge weights.

**The Core Insight: Optimal Substructure**
The key is to order vertices arbitrarily as V = {1, 2, ..., n} and define:
-   **$V_k$ = {1, 2, ..., k}**  (first k vertices)

**Optimal Substructure Lemma:**  Let P be a shortest cycle-free i-j path with all internal nodes in $V_k$.
- **Case 1:**  If vertex k is NOT internal to P, then P is a shortest i-j path with all internal vertices in $V_{k-1}$.
- **Case 2:**  If vertex k IS internal to P, then:
	-   P splits into P₁ (shortest i-k path) and P₂ (shortest k-j path)
	-   Both P₁ and P₂ use only internal nodes from $V_{k-1}$.

**Time Complexity:**  O(n³)
-   Three nested loops, each running n times.
-   O(1) work per subproblem.
-   n³ total subproblems.

**Space Complexity:**  O(n²) with optimization, O(n³) naive implementation
## Johnson's Algorithm
**Input:**  Directed graph G(V, E) with general edge lengths $c_e$ (possibly negative).  
**Output:**  Shortest-path distances between all pairs of vertices.
**Challenge:**  Handle negative edge weights while achieving better performance than O(mn²).
**The Reweighting Technique**
&rarr; The reweighting c'[u,v] = c[u,v] + p[u] - p[v] preserves shortest paths while making all edge weights non-negative.
**Correctness Claim:**  For every edge e = (u, v) of G, the reweighted length c'[u, v] = c[u, v] + p[u] - p[v] is nonnegative.
**Proof:**
-   p[u] = length of shortest s-u path in G'
-   p[v] = length of shortest s-v path in G'
-   Path s → u → v has length p[u] + c[u, v]
-   Since p[v] is optimal: p[v] ≤ p[u] + c[u, v]
-   Therefore: c[u, v] + p[u] - p[v] ≥ 0
**Running Time Analysis**
-   **Step 1:**  O(n) - form G'
-   **Step 2:**  O(mn) - run Bellman-Ford
-   **Step 3:**  O(m) - form c'
-   **Step 4:**  O(mn log n) - n calls to Dijkstra
-   **Step 5:**  O(n²) - O(1) work per u-v pair
**Total:**  O(mn log n) - Much better than Floyd-Warshall for sparse graphs!

