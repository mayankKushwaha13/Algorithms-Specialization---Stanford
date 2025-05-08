## Divide And Conquer
Take a problem, break it down into smaller sub problems which are then solved recursively and then combine the results of the smaller sub-problem to get a solution to the original problem.
## The Master Method
If T(n) $\le$ aT($\frac{n}{b}$) + O($n^d$)
then
T(n) = $\begin{cases}
O(n^d\log n) &\text{if a = b}^\text{d}&&\text{(Case 1)}\\
O(n^d) &\text{if a < b}^\text{d}&&\text{(Case 2)}\\
O(n^{\log_b a}) &\text{if a > b}^\text{d}&&\text{(Case 3)}\\
\end{cases}$

Upper Bound on the work at level j : 

$cn^d\times(\frac{a}{b^d})^j$

Interpretation 
a = Rate of Subproblem Proliferation (RSP)
b = Rate of Work Shrinkage (RWS) \
(per subproblem)

For total work you just sum it up on j from 0 to $\log_b n$