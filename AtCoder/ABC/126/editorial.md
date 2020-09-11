# Problem E
Imagine each element of A as a node in a graph. For every X, Y, Z, if Z is even then we add an edge between X and Y and label it with 0 (the parity of X and Y are the same). If Z is odd, we add an edge between X and Y and label it with 1 (the parity of X and Y are different). After processing all the given information, we will have a connected component(s). For each component, we need to use the magic once. Why? Because if we know the value of a node, we can know the value of all the nodes in its component by traversing the edges. For example if current node is 1 and we follow an edge with label 0, then we know the next node must be 1. So the problem boils down into finding number of connected components.

# Problem F
Observation: XOR of numbers from 0 to 2^m - 1 is 0, provided that m != 1.

Let's divide the problem into a few cases:
* K >= 2^M, the answer doesn't exist because no two numbers below 2^M can be XORed to be number larger or equal to 2^M
* K < 2^M:
    * M = 1, If K = 0, then output 0 0 1 1, else output -1.
    * Other case, Let X be a set of numbers between 0 to 2^m - 1 other than K. We can construct a sequence that looks like X K reverse(X) K. For every number in X, the XOR will be K because between them every number occurs even number of times except K. For number K, we can use the first observation, that is K XOR reverse(X) = 0. So K XOR reverse(X) XOR K will be K.
