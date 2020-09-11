# Problem A
Let's assume, WLOG, r <= g <= b. Let's try to separate all the blues (we need at least b - 1 other colors). If r + g < b - 1, the answer doesn't exist, else it exists.

# Problem B
Prefix sum + binary search. Just try excluding one verse at a time and calculate the number of verse that can be read.

# Problem C
Convert array b to array of position of the corresponding number in array a. Process the new position array in order. Assume we are currently processing pos at index i, it will take 2 * (pos[i] - 1 - (i - 1)) + 1 seconds to send. All pos to the right of it that is smaller than pos[i] will take 1 second to send. Do this procedure repeatedly.

# Problem D
Decision tree. Let's take a look at i-th kid. The probability that he is choosen first is 1/N. The probability to choose one of his gift is 1/ki, let's say the chosen gift is g. The probability gift g given to a child who wants it is count[g]/N, count[g] is how many children wants gift g. Sum all probability.
