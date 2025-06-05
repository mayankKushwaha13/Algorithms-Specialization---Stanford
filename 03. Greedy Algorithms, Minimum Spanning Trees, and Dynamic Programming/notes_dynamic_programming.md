# Principles of Dynamic Programming
1.  **Optimal Substructure**
    -   The optimal solution to the problem can be constructed from optimal solutions to its subproblems.
    -   Example for WIS: For the last vertex  $v_n$, the optimal solution either includes  $v_n$ (and thus excludes  $v_{n - 1}$), or it does not include $v_n$. This leads to a recurrence:
        A[i] = max⁡(A[i−1], A[i−2] + $w_i$)
        where  A[i] is the value of the optimal solution for the first i vertices, and $w_i$ is the weight of the $i^{th}$vertex.
2.  **Overlapping Subproblems**
    -   Many subproblems are solved multiple times in a naive recursive solution.
    -   DP eliminates this redundancy by storing and reusing solutions to subproblems (memoization or tabulation).
3.  **Tabulation (Bottom-up)**
    -   Fill in a table (usually an array) from smallest subproblems up to the original problem.
4.  **Reconstruction**
    -   After computing the optimal value, trace back through the table to reconstruct the actual solution (e.g., which vertices are in the optimal independent set).
        
### General Steps in Dynamic Programming

1.  **Identify Subproblems:**  
    Define subproblems whose solutions can be combined to solve larger problems.
2.  **Write a Recurrence:**  
    Express the solution to a subproblem in terms of smaller subproblems.
3.  **Compute Subproblems Efficiently:**  
    Use memoization (top-down) or tabulation (bottom-up) to avoid redundant work.
4.  **Reconstruct Solution (if needed):**  
    Trace back through your DP table to recover the actual choices that led to the optimal value.