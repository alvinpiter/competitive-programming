# Problem A
Just output 1 and X - 1

# Problem B
We can use each number in the array once, so the LIS equals to number of unique elements.

# Problem C
There are 2 cases:
* The tree has exactly 2 leaves, no matter how we put the numbers, there will always be two pairs of node whose MEX is n - 1.
* The tree has more than 2 leaves, put the number 0, 1 and 2 to the leaves and put the other numbers arbitrarily

# Problem D
There are 5 cases:
* The answer is -1 if xor > sum or the parity of xor and sum are different
* The answer is 0 if xor and sum is 0
* The answer is 1 if xor equals to sum
* The answer is 2. Use identity a + b = a xor b + 2 * (a & b). a&b = (sum - xorr)/2. a&b tells us all the bits in a and b that must be on. WLOG, let's say a = (sum - xorr)/2, so b = (sum + xorr)/2. We need to check if a&b equals to (sum - xorr)/2. If they are equal, output a and b.
* The answer is 3 if none of the above conditions is true. Output xor, (sum - xorr)/2, (sum - xorr)/2
