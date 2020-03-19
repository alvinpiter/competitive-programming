# Problem E
Observation: If there is a bridge, there will be no solution.
Proof: Assume the bridge is on edge u-v. If we direct the edge from u to v, then all nodes in component v will not be able to reach nodes in component u. The same thing happen if we direct the edge from v to u.

Observation: If there is no bridge, the answer always exist.
Proof: Keep in mind that there are two types of edges in graph, span edges and back edges. We first construct the DFS tree rooted at node 1. We direct all span edges from ancestor to descendant and all back edges from descendant to ancestor. After redirection, for each node, there will be a path from root to it and there will be a path from it to root. Hence the graph is strongly connected.
