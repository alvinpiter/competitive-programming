# Problem A, B, C
Easy, implementation

# Problem D
Observation: When sum of a is less than V, then the answer is NO.
Observation: There must be a set of tanks whose volume sum yield the same remainder when divided by K with when V divided by K.

Based on the observations above, we can implement this algorithm:
* Perform dynamic programming to decide which tanks whose volume sum will yield V (modulo K) (for now on, we call this set of tanks as set S). The formula is dp[n][k] -> Is it possible to have a subset whose sum is congruent to k in modulo K out of the first n elements.
* Define two indices, X and Y. Set X as the first element in S or 1 (if S is empty). Set Y as index other than Y.
* For all indices in set S, put its content to index X
* For all indices not in set S, put its content to index Y
* Up until now, there are only 2 tanks with water and volume of tank X is congruent to V in modulo K. Now we just need to adjust its volume to be V.

# Problem E
Maintain a set of unvisited vertices. Whenever we visit a vertex with DFS, we remove it from the set. We then iterate over the set to look for next vertex to visit. If the next vertex is already visited or there is no edge connect it with current vertex, we skip it. Notice that there will be at most 2 * m skips.

# Problem F
Observation: Each number x will only take several steps to reach D(x) = 1 or D(x) = 2. We will call number x whose D(x) = 1 or D(x) = 2 converged.

Algorithm:
* Maintain a set that stores the indices of array whose number has not converged yet.
* Maintain a binary indexed tree to answer range sum query.
* Whenever we receive an update query in range l to r. We look for elements in our set whose value is between l and r and update them (also update the BIT). If some numbers converged, we remove them from the set.
