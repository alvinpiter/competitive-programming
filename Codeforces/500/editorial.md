# Problem A
Sum all X and Y. If sum of X is smaller than sum of Y, the answer is No because that means the number of stones increased.

# Problem B
The answer is either -1, 0, 1 or 2.
Case 0: If there are duplicate in the original array, the answer is 0.
Case 1: Let's divide the numbers into two set, the one whose bit is subset of X and the whose bit is not subset of X. The answer is 1 if there is a number in second set which will result to number in first set after applying AND to it.
Case 2: Apply AND to all numbers. If there are duplicate, the answer is 2.
Case -1: If none of the above is true, the answer is -1.

# Problem C
Let's sort the array. There are two cases:
* The minimum and maximum are in the same set, let's say we use it as X values. Then we need to choose n consecutive elements as Y values.
* The minimum and maximum are not in the same set, let's say we use minimum in X and maximum in Y. Then we need to choose first n elements as X and last n elements as Y.
The proof is by exchange argument.
