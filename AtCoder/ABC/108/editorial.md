# Problem C
Assume a = x (mod K), b = y (mod K), c = z (mod K). The observation is that x = y = z.
Proof:
x + y must be congruent to 0 in modulo K. That means that z must be either x or y.

* If z is x, then 2x won't be congruent to 0 in modulo K (because the pair of x is y).
* If z is y, then 2y won't be congruent to 0 in modulo K (because the pair of y is x).

So x = y = z = w. We will choose such w where 2w = 0 (mod K). For every possible w, we will take three numbers (repetition allowed) which is congruent to w (modulo K).

# Problem D
Algorithm:
* Find the position of most significant bit in L, call it N.
* Construct graph with N + 1 vertices and 2*N edges. Vertex i is connected to vertex i + 1 by 2 edges, one with weight 0 and one with weight 2^(i - 1). Up until now, number of path from vertex 1 to N is 2*N and the total weight ranging from 0 to 2^N - 1.
* For each other on bit position, call it x, add edge from vertex x + 1 to vertex N + 1 with weight equal to sum of on previous on bits.
