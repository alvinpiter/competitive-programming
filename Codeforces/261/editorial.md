# Problem E
[THIS SOLUTION GOT MLE] Convert the given a graph into a DAG. Each node in the DAG correspond to an edge in original graph. For each neighboring edge a and b in original graph, we add edge a-b in DAG if a's weight is less than b's weight. After that, just find longest path in DAG.

Alternative solution:
Define dp[i] -> maximum number of nodes in an increasing weight path ending at i.
Let's process the edges starting from the lightest one. When we are currently at edge u-v, update dp[v] = max(dp[v], 1 + dp[u]).
We need to process the edge with the same weight simultaneously.
