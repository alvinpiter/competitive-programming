# Growing Trees
Observation: If we can keep the heights sorted after each operation, the problem becomes easy. Just perform lower bound and upper bound for every query.

Observation: To store the height updates, we can use binary indexed tree. So the final height of tree at index i is h[i] + queryBIT(i). The BIT must be able to support range update and point query.

How to keep the heights sorted after each operation? Imagine we would like to update the heights from index i to j.

Define lb as the smallest index such that height(lb) == height(j).
Define ub as the largest index such that height(ub) == height(j).

For all heights before lb, we can just just update it because after update the heights will still be sorted.
We have to be careful for heights from index lb to j, because updating it might cause the heights become out of sort (for example when height(j + 1) == height(j)). To resolve this issue, we will update the heights at the "border", i.e we will update index ub - (j - lb + 1) + 1 until index ub.

# Ice Cream
Brute force O(N^3).

# Switch the Lamp On
Model the grid as a graph. The nodes will be the corner of each cells. There are two cases:
* If current cell is \, then we connect the top left and bottom right with edge with cost 0, top right and bottom left with edge with cost 1.
* If current cell is /, then we connect the top left and bottom right with edge with cost 1, top right and bottom left with edge with cost 0.

After constructing the graph, run Dijkstra's algorithm and output the shortest path to bottom right corner. This works because for each cell, we either traverse it \ or / but not both. This can be proofed by coloring technique. If we paint the corners like we paint a chess board, then whatever we do we will always be in a corner with the same color with origin corner.

# Treasures and Vikings
For each cell, define minDViking[r][c] as minimum step needed by the viking's ship to conquer cell (r, c). Conquer here means the viking ship is in the same row or same column with the cell. minDViking can be calculated with BFS. After that, we will do BFS from our initial position. We can visit a cell if our shortest path to that cell is smaller than minDViking of that cell.
