# Problem D
Define cnt[u][d] as number of node at depth d from u. This can be calculated in O(NK) using DFS.
For each node u, we will find node v who is at distance d from it. There will be 2 cases:
* v is in subtree of u. Number of such v is cnt[u][d].
* v is not in subtree of u. To count such v, we iterate the ancestors of u. Assume we are currently at ancestor p and u is in subtree rooted at q (q is direct child of p). Then number of such v is: cnt[p][d - dist(u, p)] - cnt[q][d - dist(u, p) - 1].

With above algorithm, we will count each path twice, hence we should divide the answer by 2.
