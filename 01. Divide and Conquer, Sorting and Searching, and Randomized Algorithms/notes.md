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