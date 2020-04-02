# Problem A
If x1 != x or x2 != x then we can 'exhaust' our horizontal movement, i.e until either a or b is 0. We can also do this for vertical movement. After exhaustion, we only need to check the movement in one direction. For example, assume after exhaustion we need to move m steps to the right and n steps to the top, so we need to check if x2 - x <= m and y2 - y <= n. Similar ideas apply if we need to go left or bottom.

# Problem B
Every composite number less than 1000 can be represented with primes from set {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}. So let's just paint all multiples of 2 (if any) with color 1, all multiples of 3 (if any) with color 2, etc.

# Problem C
Observation: The period must also be palindrome.
We need to count how many characters need to be changed in order for all periods become a palindrome. Let's group the character in each period, that is the first and last character goes into first group, the second and second to the last character goes into the second group, and so on. Notice that we can solve the problem in each group exclusively. The minimum number of characters to be changed within a group equals to number of characters minus the count of character with the maximum occurence. Sum the result from each group, that is the answer.

# Problem D
The idea is to trick the dynamic programming solution to produce 0 at the right end of the matrix and make sure there is a path with AND values equal to k. See the matrix in the code.

# Problem E
Observation: If the parity of all the cells are the same, then we can always make them to be equal height by using operation 2. Hence we only need to deal with cells parity.

Define a connected component as a set of cells with same parity such that from one cell we can go to another cell by going up, right, down or left.

Observation: We can always group all cells with the same parity into one connected component using operation 1.

Observation: We can change the parity of all cells of a connected component whose size is even.
Proof: Operation 1 either decreases size of connected component by 0 or 2.

Observation: We can't change the parity of all cells of a connected component whose size is odd.
Proof: Operation 1 either decreases size of connected component by 0 or 2.

Observation:
Let szOdd and szEven be the size of connected component whose cells parity is 1 and connected component whose cells parity is 0. There are a 2 cases:
* One of szOdd or szEven is even -> We can make the parity of all the cells the same
* Neither szOdd nor szEven is even -> We can't make the parity of all the cells the same
Proof: Same with previous observation

Final solution:
Define allWays = (R - L + 1)^mn, as number of ways to choose numbers in range L..R to fill grid with size n*m.

If nm is odd, the the answer is allWays. Otherwise we need to exclude cases where szOdd is odd and szEven is odd.

invalidWays = sum(C(mn, k) * E^k * O^(mn - k)), for all odd k <= mn - 1, E and O is number of even and odd number from L to R respectively.

The invalidWays can be counted by using Newton's binomial theorem. Explore the expansion of (O + E)^mn and (O - E)^mn.

invalidWays = 1/2 * ((E + O)^mn - (E - O)^mn)
valid ways = allWays - invalidWays
