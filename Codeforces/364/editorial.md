# Problem 1B
For each node u, count how many universities are in subtree rooted at u. For each node u, we must connect all universities in its subtree with universities not in its subtree. Therefore path from u to its parent will contribute min(numUni[u], 2 * K - numUni[u]).
