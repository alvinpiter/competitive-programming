# Problem A
Just simulate the process and store the result in a set because number of possibilities is small.

# Problem B
Find the smallest index where the number in that position can be mapped into larger number. Starting from that index, map the number while the mapped number is not less than the original number.

# Problem C
Notice that it is always better to take the smallest (yet larger than last taken number) between the left-most and right-most number. In case the left-most and right-most number is a tie, notice that we will only take numbers from one side. Choose the side which has longest increasing sequence.

# Problem D
Algorithm:
* Allocate i problems at the i-th day. If the sum of problems is more than N, then the answer is NO. Otherwise continue to next step.
* Assuming now there are `leftOver` problems left. Divide it evenly to K days.
* As of now, the `leftOver` problems must be less than K and all conditions are satisfied. If leftOver is 0, print the answer. Otherwise continue to next step.
* Carefully do case by case analysis:
    * K = 1. Nothing to check, it is always possible
    * K = 2. There is 1 `leftOver`. Put it on 2nd day and check the a2 <= 2*a1 condition
    * K = 3. If N = 8, answer is NO. Otherwise put the `leftOver` on 3rd day.
    * K > 3. if `leftOver` is 1, put it on K-th day, else put `leftOver` - 1 on Kth day and 1 on (K-1)-th day. Notice that this will not violate any conditions.

# Problem E
For a number x, notice it will produce smallest remainder when paired with n - x, n - x + 1, .., n - 1, 0, 1, .., n - 1 (in this order). We can put the available pairs in a set and for every x, we find its pair. The pair is either lower_bound(x) or the smallest number in the set.

Alternative solution: Use BIT and binary search to count available pairs.

# Problem F
Observation: If the minimum number in the circle is a and the maximum number in the circle is b, then all numbers from a to b (inclusive) must exist in the circle.
Proof: Proof for b - a == 0 && b - a == 1 is obvious. For b - a >= 2, we can proof by contradiction. Assume there is a number x, where a < x < b and x does not exist in the circle. Then the circle won't be valid because we can't connect the numbers to the left of x and the numbers to the left of x.

If we want to construct circle with minimum number a and maximum number b, then there are 3 cases:
* b - a == 0, this is easy
* b - a == 1, this is easy too
* b - a >= 2, all numbers from a + 1 and b - 1 must appear at least twice and the circle can be constructed this way: a, a + 1, ..., b, b - 1, b - 2, .., a.

With above observations, this problem can be solved with brute force + a little bit of dp (to find sequence of numbers that appears at least twice).

# Problem G
Observation: There is a solution where the first row is not toggled.
Proof: Let's say there is a solution where first row is toggled. We can construct another solution by toggling all rows and all columns that is not in this solution. Why is this true? All intersection cells in first solution will change it's parity by 2 (which is equivalent to 0), while the same intersection will will change it's parity by 0 in the second solution, hence the parity change is the same. The same argument applies for all non-intersection cells.

With that observation, we can construct a brute force on the number of 0's in the first row. There are two cases:
* The number of 0's in first row is < M: All other rows should be 1. Solution construction is easy.
* The number of 0's in first row is M:
    * Find the row where there is mixed parity, if there are more than one, then the answer doesn't exist.
    * If there is no row with mixed parity, make sure the matrix will contain all 0.
    * If there is one row with mixed parity, make sure every row before it contain all 0 and every row after it contain all 1 and the row with mixed parity can be toggled to become 0000..111 (i.e 0's followed by 1's)

Tedious to code T_T
