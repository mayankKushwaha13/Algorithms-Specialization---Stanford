# Greedy Algorithms
&rarr; Iteratively make “myopic” decisions, hope everything works out at the end.
Example : Dijkstra's shortest path algorithm.

# Minimum Spanning Tree
&rarr; For an undirected connected graph G(V, E) with a cost $\sf c_{e}$ for each edge e ∈ E, minimum cost tree T ⊆ E that spans all vertices, where :
-   T has no cycles.
-   The subgraph (V, T) is connected (contains path between each pair of vertices).
-   Minimizes the sum of edge costs.

### Fundamental Graph Theory Concepts
-   **Cut:**  A partition of V into two non-empty sets A and B.
-   **Empty Cut Lemma:**  A graph is not connected ⟺ ∃ cut (A, B) with no crossing edges.
-  **Double Crossing Lemma:** Suppose the cycle C ⊆ E has an edge crossing the cut (A, B), then so does some other edge of C.
-   **Lonely Cut Corollary:**  If e is the only edge crossing some cut (A,B), then it is not in any cycle.
### The Cut Property - Key to Correctness
**Cut Property:**  Consider an edge e of G. Suppose there is a cut (A, B) such that e is the cheapest edge of G that crosses it. Then e belongs to the MST of G.
This property  **implies correctness**  of both Prim's and Kruskal's algorithms because:
-   **Prim's:**  Every edge added is explicitly justified by the Cut Property.
-   **Kruskal's:**  Each edge satisfies the Cut Property when added.