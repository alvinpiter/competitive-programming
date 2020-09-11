# Problem A
n = a1 + a2 + .. + ak for some odd numbers a1, a2, .., ak. We can rewrite ai as 2*ai' - 1, where ai' >= 1.

n = 2(a1' + a2' + .. + ak') - k
n + k = 2(a1' + a2' + .. + ak')

(n + k) must be divisible by 2 and (n + k)/2 must be at least 1 + 2 + .. + k.

# Problem B
Easy, just simulate the process and check if all the princess is matched.

# Problem C
Move left m - 1 times. This guarantee all the chips will be in the first column.
Move up n - 1 times. This guarantee all the chips will be in the first column and the first row.
From here, take all the chips visiting all the grid with zigzag movement, i.e go right as much as possible, go down, go left as much as possible, etc.
The total number of moves will be <= 2 * m * n.

# Problem D
Observation: We can make a graph by connecting i and p[i]. This graph will contain 1 or more cycles.
Observation: From some cycle, we can make smaller cycle by hopping. For example there is a cycle 1, 2, 3, 4 (then 1). We can make smaller cycles by hopping 2 nodes at a time, the resulting cycles will be 1-3 and 2-4. The hop size must be the divisor of cycle length. Notice that the hop size here is a potential answer to the problem. Hopping 2 nodes a time means that we power our permutation by 2.

With those observations, the solution would be:
* Generate all cycles
* From each cycle, try to generate all sub-cycle and check if there is a cycle with nodes with the same color.

# Problem E
Assume we want to count how many blocks of size sz. There are two cases:
* The block is located at the beginning or end of the string:
    * There are 10 ways to choose the number for this block
    * There are 9 ways to choose the number immediately after/before this block
    * There are 10^(N - sz - 1) ways to choose the other numbers
    * There are two possible position for this block (beginning or end)

* The block is not located at the beginning or end of the string:
    * There are 10 ways to choose the number for this block
    * There are 81 ways to choose the number immediately after/before this block
    * There are 10^(N - sz - 2) ways to choose the other numbers
    * There are (N - sz - 1) position for this block (from index 2 until index N - sz)
