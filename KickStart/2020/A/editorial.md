# Allocation
Sort the house price in non-decreasing order and then start buying from the cheapest one.

# Plates
Dynamic programming, dp[n][rem] = maximum possible score if we are processing the first n stacks and we can take rem plates.

# Workout
Let's define a function f(x) as minimal number of session to be added to make so that the gap between any two consecutive session is at most x.
f(x) will be monotonically decreasing, so we can use binary search to look for optimal value of x. Now let's see how we implement f(x). We look at every 2 consecutive session, then there are two cases:
* The gap is <= x, then we do nothing
* The gap is > x, then we should add some sessions in between. The number of session to be added is floor(gap/x) or gap/x - 1, depending on whether gap is divisible by x.

# Bundling
We will calculate how much each prefix contributes to the final answer. Let's say we have a prefix P.
* We count how many other strings shares the prefix of P of length 1, let it be count1.
* We count how many other strings shares the prefix of P of length 2, let it be count2.
.
.
* We count how many other strings shares the prefix of P of length |P|, let it be count|P|.

In optimal solution, each of those count will contribute floor(count|i|/K) to the final answer. In order to calculate this, we can use trie data structure.

Side note: You can visualize it like this, imagine puting the string on N lines and perform "sorting" on it. When "sorting", we compare the length of shared prefix. We put strings with largest shared prefix on top of the lines.
