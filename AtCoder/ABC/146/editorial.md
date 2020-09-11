# Problem D
K is the maximum indegree of a node. To assign color to the edges, use DFS.

# Problem E
Let sum[i] = sum(A1, A2, .., Ai).

We want to find two indices i and j such that:
(sum[j] - sum[i - 1])%K = j - i + 1

sum[j] - sum[i - 1] = K*x + (j - i + 1)

(sum[j] - j) - (sum[i - 1] - (i - 1)) = K * x
(sum[j] - j) - (sum[i - 1] - (i - 1)) == 0 (mod K)

For each j, we can find such i using map. Also we want to limit our choice of i, we want only i which j - i + 1 <= K. To accomodate this, we can use sliding window.
