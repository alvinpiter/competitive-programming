# Problem A
Just distribute sum to c evenly, sum/c + remainder if any.

# Problem B
Notice the sum of the two numbers modulo 3 is invariant, hence the answer does not exist if (a + b)%3 != 0. WLOG, let's say a <= b. If b > 2 * a, there is no answer. Else there is answer.

# Problem C

# Problem D
Let's say the minimum agility of our chosen soldier is x and we can go to N + 1, then we can also go to N + 1 if the minimum agility is x + 1. This calls for binary search solution. For each x, we know well see which traps that might kill our soldier. For each of those traps, we have to disarm it first. Notice that the point with a trap need to be traversed 3 times, once we go alone, once we go back, once we go with the squad. Hence the total answer is N + 1 + 2*C, where C is the number of point that is covered by a trap.
