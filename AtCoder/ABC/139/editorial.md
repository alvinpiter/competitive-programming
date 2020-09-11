# Problem D
Let's say the element of our permutation is x1, x2, .., xn.
We want to maximize the following value: (1 mod x1) + (2 mod x2) + ... + (n mod xn). Notice that the i-th term's maximum value is i - 1. So we can construct optimal solution as follows: x = {N, 1, 2, 3, .., N - 1}. The answer is 0 + 1 + 2 + .. + (N - 1).

# Problem E
Create a new directed graph where each node is a match object between two players. If match a must occur before match b, then we add a directed edge from a to b. If there is a cycle in the graph, then it's impossible to schedule the matches. Otherwise, each day we schedule matches that doesn't have pre-requisite (indegree = 0) simultaneously.
