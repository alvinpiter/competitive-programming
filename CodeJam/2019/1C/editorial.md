# Robot Programming Strategy
In order to be sure to win the tournament, we have to beat everyone else. Now consider playing against all the opponents at once. Take a look at current hand of opponents. There are 3 cases:
* There is only one unique hand. This is easy win for us.
* There are two different hands. We need to choose the one that beats the other and then proceed to next round.
* There are three different hands. No matter what hands we use, we will lose, so this is IMPOSSIBLE case.

Notice that after each round at least 1 opponent will be removed from opponents list, so the depth of our recursive solution will be more or less equals to A.

# Power Arrangers
Assume we are currently looking for the i-th character of the missing permutation. Make a guess at corresponding positions. If some character occurs exactly factorial(5 - i - 1) - 1 times (and this character has not been included to answer), then this is the missing character at i-th index. In the next guess, we can eliminate all permutations that does not share same prefix with our answer. The number of operations we will need is roughly 119 + 23 + 5 + 1 = 148
