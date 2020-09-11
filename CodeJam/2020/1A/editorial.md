# Problem A
For each string, divide it into 3 smaller strings:
* Characters before first asterisk (let's call it prefix)
* Characters after last asterisk (let's call it suffix)
* Characters between first and last asterisk (let's call it middle)

To construct the answer, we can do the following:
* Validate the prefixes. All the prefixes must share the same prefix. If not, then answer is *.
* Validate the suffixes. All the suffixes must share the same suffix. If not, then answer is *.
* Just merge all the middle string.
* The answer is prefix + middle + suffix.

# Problem B
If we can just choose some row in the triangle, the problem is easy, just pick each row i such that the i-th bit of N in binary representation is on. Since we can't just pick some rows, we will have to tweak our algorithm a bit. New algorithm:
* Instead of constructing N, we construct N - 30.
* For every on bit in N - 30, we take the whole row in the triangle. And for every off bit, we will take 1 in the row (either the left most or right most).
* By this time, the total number we take is <= N. If < N, then just take 1's (we will need no more than 30).

The total numbers we will take will be <= (1 + 2 + .. + 29) + 30 < 500.

# Problem C
In each round we only need to check the neighbors of the previously eliminated players. Since each player is eliminated at most once, the total complexity will be O(R * C). The reason is because each player has at most 4 neighbors.
