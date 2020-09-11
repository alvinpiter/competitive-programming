# Problem A
The answer is equal to N - prefix0 - suffix0 - numOne, where N is length of string, prefix0 is number of consecutive 0 in prefix, suffix0 is number of consecutive 0 in suffix, numOne is number of 1 in string. Beware the case when numOne equals 0, output 0.

# Problem C
Let's divide the problem into two cases:
* If length of password is 1, the answer is obvious.
* If length of passowrd is not 1, let's keep track the neighbors of all characters. If there is a character who has more than 2 neighbors, the answer is NO. If number of character who has exactly 1 neighbor is not 2, the answer is NO. If the answer is YES, then we can construct the solution by following the chain of neighbors.

# Problem D
Count how many boxes with size lg, for each lg <= 60. Process N from the least significant bit. If we can merge smaller boxes to fulfill current bit, merge these boxes. If we can't, we find the first larger box and then we divide it.
