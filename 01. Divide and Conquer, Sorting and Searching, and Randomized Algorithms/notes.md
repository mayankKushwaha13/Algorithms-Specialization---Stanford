## Divide And Conquer
Take a problem, break it down into smaller sub problems which are then solved recursively and then combine the results of the smaller sub-problem to get a solution to the original problem.
## The Master Method
![alt text](image.png)
Upper Bound on the work at level j : 

$cn^d\times(\frac{a}{b^d})^j$

Interpretation 
a = Rate of Subproblem Proliferation (RSP)
b = Rate of Work Shrinkage (RWS) \
(per subproblem)

For total work you just sum it up on j from 0 to $\log_b n$

# Graphs
* Vertices (Nodes)
* Edges (Pairs of Vertices)
  * Can be directed (ordered, arcs) or undirected
 ## Cuts of Graphs 
 Partition V into two non empty disjoint subsets
 Crossing edges :
 &rarr; one endpoint in each A and B (undirected)
 &rarr; tail in A, head in B (directed)
**Minimum Cut :** 
&rarr; A cut with fewest number of crossing edges.
* Applications
	* Identifying network bottlenecks/weaknesses <br> &rarr; A minimum cut reveals critical points in network infrastructure where a small number of edge removals could disconnect the network
	* <u>Community detection in Social Networks </u> <br> &rarr;  Finding minimum cuts to partition the network into groups with the fewest connections between them.
	* Image Segmentation <br> &rarr; Minimum cuts to separate an image into meaningful regions with minimal "disagreement" across the boundary. <br> &rarr; This process involves: 
		-   Representing an image as a graph where pixels are nodes
		-   Assigning edge weights based on pixel similarity (color, intensity, texture)
		-   Using these weights to determine which pixels likely belong to the same object
		-   Applying minimum cuts repeatedly to identify distinct objects within the image. 
		&rarr; The edge weight principle is crucial: a high weight between pixels u and v indicates they likely belong to the same object.

**Edge Weight :** A numerical value assigned to an edge that represents some attribute of the connection between two nodes.

 **Sparse v/s Dense Graphs**
&rarr; In a sparse graph, number of edges m is closer to O(n) where n is number of vertices
&rarr; In a dense graph, m is closer to $\Omega$($n^2$)

---
### Adjacency Lists and Adjacency Matrices
**1. Adjacency Lists**
A graph is represented using two arrays: <br> &rarr; *Vertices array*: Stores all vertices.
&rarr; *Edges array*: Stores all edges, with each edge pointing to its two endpoints.
-   Space Complexity :  O(n+m) 
-   Efficiency:
    -   Iterating over edges incident to a vertex:  O(degree(v)).
    -   Checking if two vertices are connected:  O(degree(v))  (inefficient for this operation).
-   Use Cases:
    -   Sparse graphs (where  $m \ll n^2$).
    -   Algorithms requiring traversal of edges (e.g., BFS, DFS, Dijkstra’s algorithm).
---
**2. Adjacency Matrices**
A 2D array where entry (i, j) is 1 if there’s an edge from vertex  i  to  j, and 0 otherwise. For weighted graphs, entries store edge weights.
-   Space Complexity:  O($n^2$), making it inefficient for sparse graphs.
-   Efficiency:
    -   Checking edge existence:  O(1).
    -   Iterating over all edges:  O($n^2$) (inefficient for sparse graphs).
-   Use Cases:
    -   Dense graphs (where  $m \approx n^2$ ).
    -   Applications requiring frequent edge-existence checks (e.g., small graphs in dynamic programming).

## Random Contraction Algorithm
&rarr; Karger's Random Contraction Algorithm is a <u>randomized Monte Carlo method</u> to find the **minimum cut** in an <u>undirected graph</u>.
### Algorithm Steps
1.  **Contraction**:
    -   Randomly select an edge  (u, v).
    -   Merge u and v into a single "supernode."
    -   Redirect all edges incident to u or v to the supernode.
    -   Remove self-loops (edges from the supernode to itself).
2.  Repeat contractions until only  **two supernodes**  remain. The edges between them form a cut.
3.  Iterate  the entire process multiple times and return the smallest cut found.
### Probability of Success
&rarr; Probability that an edge crossing the min cut (A, B) is chosen in first iteration,
P[$S_1$] = k / m ; k &rarr; number of crossing edges.
&rarr; degree of each vertex v &geq; k
(**Degree of a vertex** is the number of edges incident to it.)
&rarr; &Sigma; degree(v) = 2m &geq; kn
&rarr; P[$S_1$] &leq; 2 / n
&rarr; P[output is min cut (A, B)] = P[never contracts a crossing edge in min cut]<br>=P[$S_1' \cap S_2'\cap S_3'....\cap S_{n -2}'$ ]
&rarr; P[$S_1' \cap S_2'$] = P[$S_2'/S_1'$] &middot; P[$S_1'$] 
&rarr; P[$S_2'/S_1'$] &leq; 1 - 2 / (n - 1)
&rarr; Putting all together we get P[success] &geq; $\frac{1}{n^2}$
Running time of Karger's Algorithm is polynomial in n and m, but slow $\Omega(n^2m)$.
We can get speed ups to roughly $\Omicron(n^2)$.
## Number of Minimum Cuts
&rarr; A tree with n vertices has n - 1 min cuts.
&rarr; Largest number of min cuts a graph with n vertices may have = $^nC_2$
&rarr; Minimum number of min cuts for a graph in general = n - 1
&rarr; Minimum number of min cuts for a cycled graph = $^nC_2$
