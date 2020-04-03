# Problem A
When current number of bacteria is odd, that means we need to add 1 bacteria today. Because the result from yesterday's bacteria must be even.

# Problem B
Greedy. Pair the people from the largest score.

# Problem C
Point (a, b) is either on the increasing slope or decreasing slope. Derive the equation and constraint then perform binary search to find the solution.

# Problem D
Observation: Multiplying a number by x (x >= 2) will at least shift its most significant bit by 1 position to the left.

Observation: We want to make the significant bit in the result to be as large as possible.

Observation: It's optimal to allocate all operations into one number.
Proof: Assume there is a solution where we don't allocate all operations into one number. Let's see the largest number y. We can make the result larger by allocating other operations into y (there must be at least one, because in the beginning of proof we claim we don't allocate all operations into one number).

# Problem E
Let's solve a simpler problem first. Assume we know the number x, how do we find the weakness of the sequence?

Define prefix[j] = sum of elements from index 1 to j
Define f(i, j) = prefix[j] - prefix[i - 1]
Define g(i, j) = -prefix[j] + prefix[i - 1]

The weakness of the sequence is the maximum value of f(i, j) and g(i, j) over all 1 <= i <= j <= n.

In order to maximize f(i, j), we can iterate over all j and find smallest prefix[i - 1] using RMQ. g(i, j) is calculated with the same trick.

So, if we know x, we can solve the problem in O(n).

Now we need to decide what x should be. Notice that the larger x, max f(i, j) will be smaller and max g(i, j) will be larger. This means that if max f(i, j) is still larger then max g(i, j), we can make x larger and it will yield better result. Hence we can do binary search on x. The final complexity is O(n log n).
