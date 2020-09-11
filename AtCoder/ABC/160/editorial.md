# Problem A, B
Easy

# Problem C
The answer is K - largestDistanceBetweenTwoHouse.

# Problem D
When calculating shortest path from i to j (i < j), we can consider three kinds of path:
* Go straight from i to j
* Go to X then Y then j
* Go to Y then X then j
Take the minimum between those three.

# Problem E
My solution:
Let's say set of red apples as set A and set of green and colorless apples (merged) as set B.
In set B, we need to know the color of each element, it is either green or colorless.

Sort set A and set B non incrasingly.
Initially we take X apples from set A and Y apples from set B.
We then do bruteforce on number of red apples taken from set A, starting from X and goes down to 0.

Define 2 pointers on set B:
* ptr1 points to first colorless apples that is still in set B
* ptr2 points to the last apple in set B that is taken as green apples. Initially it points to Y - 1

Notice that whenever we want to take a colorless apple from set B, we need to update ptr1 and ptr2 if ptr1 <= ptr2. Here is what to update:
* Take another green apple (it is located in ptr2 + 1)
* Set ptr1 to the next colorless apples
* Also update current sum of red apples and current sum or green apples

# Problem F
Dp + re-rooting technique. When calculating DP, use multinomial coefficient technique.
