# Graph Search
**Motivations for Graph Search:**
-   **Network Connectivity:**  Determine if a network is connected (can you get from any node to any other?).
-   **Pathfinding:**  Compute routes, e.g., driving directions.
-   **Planning:**  Represent and solve problems like puzzles (e.g., Sudoku) as graphs, where nodes are partially completed puzzle and edges are possible moves.
-   **Component Analysis:**  Identify connected parts of a graph, useful for clustering, web analysis, etc.
### Generic Graph Search Algorithm
Explore all nodes reachable from a starting vertex, without revisiting any node:
1.  **Initialization:**
    -   Mark the starting node (s) as  _explored_.
    -   All other nodes are  _unexplored_.
2.  **Exploration Loop:**
    -   While possible, select an edge (u, v)  where u is  _explored_ and v is  _unexplored_.
    -   Mark v as  _explored_.
    -   Repeat until no such edges remain.

At the end if vertex v is explored &rArr; graph G has a path from s to v.
### Variants: BFS and DFS

The generic search can be specialized based on how the next node is chosen:
|Algorithm  | Data Structure |Exploration Strategy|Key Applications|
|--|--|--|--|
| **BFS** |Queue (FIFO)|Layer by layer|Shortest paths, undirected connectivity|
|**DFS**|Stack (LIFO) or Recursion| Deep, aggressive|Topological sort, strongly connected components

-   **BFS**  explores nodes in increasing order of distance from the start, making it ideal for shortest-path and connected component tasks in undirected graphs.
-   **DFS**  explores as far as possible along each branch before backtracking, which is useful for tasks like topological sorting and identifying strongly connected components in directed graphs
- **Efficiency** : O(n + m)
### BFS Application : Undirected Connectivity
**Connected Components :** u &harr; v &hArr; there exists a path between u and v in G, and this relation is an equivalence relation.
Why compute all connected components?
   -   <u>Check if the network is disconnected:</u>
        -   Determining if there are isolated groups in the network that cannot communicate with each other.
    -   <u>Graph Visualization:</u>
        -   Understanding the structure of the graph.
    -   <u>Clustering:</u>
        -   Grouping related nodes together, which is useful in data analysis, social networks, etc.