# Problem A
The leftmost position reachable is equal to number of L's in the string, rightmost position reachable is equal to number of R's in the string. The answer is the same of these counts plus 1 (origin).

# Problem B
The sum of segment that will be chosen by Adel can be formulated by allSum - prefixSum - suffixSum or allSum - prefixSum or allSum - suffixSum. If some prefixSum or suffixSum is non-positive, Adel will have a way to choose cakes with larger or equal sum to Yasser's, so the answer will be NO. Otherwise the answer is YES.

# Problem C
Since LCM of a and b equals X, a and b must be divisor of X. We try all possible pairs of a and b and check if their LCM equals X.

# Problem D
Assume we are currently working on i-th bit (we start working from the most significant bit). Let's divide the numbers into two set, let's say setOn and setOff. setOn will have all the numbers whose i-th bit is on and setOff will have all the numbers whose i-th bit is off. If one of these sets is empty, then the i-th bit in our answer will be off. Otherwise, the it-th bit in our answer will be on. There are two cases:
* X's i-th bit is off. We will have to minimize the maximum result in setOn, because the result in setOff must be smaller.
* X's i-th bit is on. We will have to minimize the maximum result in setOff, because the result in setOn must be smaller.
