# 1140
Dynamic programming. Define dp[i] as the maximum number of money can be earned considering i-th to N-th projects. We first sort the projects in increasing order of starting day. Whenever we take a project, the next project taken should have starting day larger than current project's ending day. To look for next project, we can use binary search.

# 1203
Shortest path graph + finding articulation point. Let's first define "shortest path graph". For a graph G = (V, E) and two nodes as origin and destination, shortest path graph G' is defined as G' = (V', E') where V' = V and E' is subset of E such that each element of E' might be traversed by shortest path from origin to destination. Here is how to construct shortest path graph:
* Run Dijkstra's algorithm from origin
* Run Dijkstra's algorithm from destination
* For each edge u-v of original graph, if `distance_from_origin_u + cost + distance_from_destination_v == distance_from_origin_N`, then this edge is included to E'. Keep in mind that elements of E' are undirected.

After constructing G', we find its articulation points.

# 1654 (Unsolved)
Define `set-on-i` as set of numbers whose i-th bit is on.
Define `set-off-i` as set of numbers whose i-th bit is off.

Assume we are currently processing number x.
* Number y such that x | y = x is element of intersection of sets `set-off-i1`, `set-off-i2`, .., `set-off-ik`, where i1, i2, .. ik are the off bit positions of x.
* Number y such that x & y = x is element of intersection of sets `set-on-i1`, `set-on-i2`, .., `set-on-ik`, where i1, i2, .. ik are the on bit positions of x.
* Number y such that x & y = 0 is element of intersection of sets `set-off-i1`, `set-off-i2`, .., `set-off-ik`, where i1, i2, .. ik are the on bit positions of x.

Keep in mind that we only to count the number of elements of each intersections, not the elements itself. We will now define 2 functions:
* countOn[mask] = Number of elements x such that every on bit position in mask is also on bit position in x.
* countOff[mask] = Number of elements x such that every off bit position in mask is also off bit position in x.

Knowing countOn[mask] and countOff[mask], the the answer for number x is just countOff[x], countOn[x], N - countOff[invert(x)]

# 1677
Union-Find + offline queries processing. By processing the queries offline and from last to first query, we are actually dealing with merging operation instead of breaking operation. Calculating number of components after merging is easy with union-find data structure.

# 1731
Dynamic programming + Trie. Define dp[i] as number of ways to construct suffix s[i..N] using words from dictionary. dp[i] = sum(dp[j]), where s[i..j-1] is a word from dictionary and i <= j. To check if a string is from dictionary, use trie data structure.

# 1745
Dynamic programming. Define dp[i][j] as "is it possible to take subset of first i coins such that the sum is j?". We can drop the first parameter in the dp state, the trick is in filling the dp table. For each i, we fill dp value from the one with largest j first.

# 1756
DFS. Run DFS, and calculate the DFS time of each node. For each edge, direct it from the node with lower DFS time to the node with higher DFS time.
