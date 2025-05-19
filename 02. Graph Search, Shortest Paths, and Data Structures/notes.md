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

### DFS Properties
* At the end if v is marked explored &hArr; there exists a path from s to v in G.
* Running time is $\Omicron(n_s+m_s)$, where :
	* $n_s$ is number of nodes reachable from s.
	* $m_s$ is number of edges reachable from s.
	&rarr; Looks at each node at most once, and each edge at most twice.

### DFS Application : Topological Sort

**Definition :** A topological ordering of a directed graph G is a labeling f of G's nodes such that :
 * The f(v)'s are the set {1, 2, 3, .., n}
 * (u, v) &isin; G &rArr; f(u) < f(v) [Head has higher value than tail].
 
**Why Important?** To sequence tasks while respecting <u> precedence constraints.</u>
* Precedence constraints simply means one tasks is to be done before another.

If there is directed cycle &rArr; no topological ordering
Every directed acyclic graph has a 'sink' vertex.

### Strongly Connected Components
**Definition** : SCCs of a directed graph G are the equivalence class of the relation :
u &harr; v &hArr; there exists a path u &rarr; v and a path v &rarr; u in G

Computing SCCs is important for:
1.  Understanding the structure of directed graphs
2.  Analyzing the Web graph (as in the famous "Bow Tie" structure)
3.  Preprocessing for other graph algorithms

**The Meta-Graph Structure**
When we identify all SCCs in a graph, they form an "acyclic meta-graph"
-   Each SCC becomes a meta-node
-   Directed edges exist between SCCs if there's at least one edge connecting vertices from different components
-   This meta-graph must be acyclic (otherwise, the components would merge into a single SCC)

This creates a useful "two-tier" structure:
-   Zooming out: A directed acyclic graph (DAG) of SCCs
-   Zooming in: The detailed structure within each SCC

**Kosaraju's Algorithm**
1.  **Reverse the Graph**: Create Gᵣₑᵥ by reversing all edges in G
2.  **First DFS Pass**: Run DFS-Loop on Gᵣₑᵥ to compute finishing times f(v) for each vertex
3.  **Second DFS Pass**: Run DFS-Loop on the original graph G, but process vertices in decreasing order of finishing times
4.  **Identify SCCs**: Vertices that share the same "leader" (the first vertex from which they were explored in the second pass) belong to the same SCC.
* Time Complexity : O(n + m).

**Finishing time** refers to a specific timestamp assigned to each vertex when DFS completes its exploration of that vertex and all its descendants.
1.  For any vertex u, discovery time $\sf u_d$ is always less than finishing time $\sf u_f$.
2.  The vertex with the highest finishing time in a DFS must be in a "source" SCC (one with no incoming edges from other SCCs).
3.  In a directed acyclic graph (DAG), <u>the reverse of the finishing times provides a valid topological ordering.</u> 

<u>Why Finishing Times Matter in Kosaraju's Algorithm</u>
1.  During the first DFS on the reversed graph, vertices are assigned finishing times.
2.  In the second DFS on the original graph, vertices are processed in decreasing order of finishing times.
3.  This ordering ensures that the algorithm processes SCCs one by one, starting from "sink" components.

## The Web Graph
The Web graph is a directed graph representation where:
-   **Vertices**: Web pages
-   **Directed edges**: Hyperlinks between pages
This representation allows us to analyze the structure of the World Wide Web as a network, revealing patterns that would otherwise be difficult to discern.
### The Bow Tie Structure
 1. Giant SCC
	-   The "core" of the web
	-   Pages in this component can reach each other through hyperlinks
	-   Well-connected with "small world" properties.
2. IN Component
	-   Pages that can reach the SCC but cannot be reached from it
	-   Examples include new web pages that link to established sites but haven't yet been linked to
3. OUT Component
	-   Pages that can be reached from the SCC but cannot reach back to it
	-   Examples include corporate websites that are linked to but don't link back to the broader web
4. Tubes and Tendrils
	-   Connect the IN and OUT components without going through the SCC
	-   Or hang off the IN and OUT components without connecting to the SCC
### Key Findings About the Web Structure
1.  All four major parts have roughly the same size.
2.  Within the CORE, pages are very well connected with "small world" properties.
3.  Outside the core, the web is surprisingly poorly connected.
4.  This structure has important implications for web search, information dissemination, and understanding how new information propagates.
### Modern Web Research Directions
1.  **Temporal aspects**: How the web graph evolves over time.
2.  **Informational aspects**: How new information propagates throughout the Web, blogosphere, or Twitter.
3.  **Finer-grained structure**: Defining and computing communities in information and social networks.