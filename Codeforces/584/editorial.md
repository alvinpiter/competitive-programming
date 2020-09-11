# Problem A
Sieve

# Problem B
Simulate

# Problem C
Brute force on the number that gets color 1 and gets color 2. Fix some value v, and do:
* Color all numbers that is less than v with color 1.
* Color all numbers that is larger than v with color 2.
* For number that is equal to v:
    * If it is to the left of leftmost number with color 2, color it 2.
    * If it is to the left right of rightmost number with color 1, color it 1.
* Check if the coloring is okay.

The reason we do step 3 is because at some solution, same number at two different indices might be colored with different color.

# Problem D
Model the problem as a graph. The nodes are the snacks and connect two snacks u and v with an edge if there is a cow who likes u and v.

If the graph is a forrest, there is always some ordering such that all the cows will be satisfied. Hence the edge that makes a cycle in the graph will be counted as sad cow.
