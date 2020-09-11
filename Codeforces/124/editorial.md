# Problem 1A
Store the positions of each character in a vector. Greedily take the lexicographically maximum character and add it to answer string while possible.

# Problem 1B
Perform BFS on infinite grid. For each cell of original grid, we keep 2 values:
* visited[r][c] -> Have we visited it before
* where[r][c] -> Where we visited it
When we want to visit an already visited cell, we check it's where values. If the where value is different, then the answer is Yes.

Why is this true?
If we can visit a cell on original grid at 2 different positions on infinite grid, than we can circle back and forth between these 2 cells.
