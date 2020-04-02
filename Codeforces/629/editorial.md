# Problem A
Easy

# Problem B
Observe the pattern. bb, b_b, bb_, b__b, b_b_, bb__, etc

# Problem C
Assume idx is the smallest index where s[idx] == 1. For i < idx, a[i] and b[i] should be the same. For i = idx, a[i] = 1 and b[i] = 0. For i > idx, always maximize b, because a is already larger than b.

# Problem D
Let's divide the problem into a a few cases:
* If number of unique types is 1, then we can use only 1 color.
* If number of unique types is 2, then we can use only 2 color.
* if number of unique types is more than two, then the answer is at most 3. There are 2 cases:
    * n is even. We can only use 2 colors with pattern like 1, 2, 1, 2,...
    * n is odd. There are 2 cases again:
        * There are 2 adjacent figures with the same type. Then the answer is 2. Assume the index i where t[i] == t[(i + 1)%n]. Paint (i + 1)%n with 1, the next with 2, and so on.
        * There is no 2 adjacent figures with the same type. Then the answer is 3. The color would be 1, 2, 1, 2, .., 3.

# Problem E
For each query, find the deepest node, let's call it node u. For each node v in the query, if lca(v, u) is not v and lca(parent[v], u) is not parent[v], then the answer is No. Otherwise the answer is Yes.

# Problem F
Observation: There is an element that does not need to change.

Observation: After we fix some element that does not change, we either equalize the lower element and then the higher element or equalize the higher element then the left element. We just need to take the minimum between those two.
