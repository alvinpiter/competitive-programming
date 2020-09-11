# Problem A
If we look at the derivative of the function, we will see that it will reach maximum in x = sqrt(d) - 1. To avoid rounding or off-by-1-error, just try every x in range 0..sqrt(d).

# Problem B
ab + a + b = a * 10^|b| + b
ab + a = a * 10^|b|
b + 1 = 10^|b|

Answer is A * number_of_possible_b

# Problem C
Consider the sequence a1, a2, .., am, bm, bm-1, .., b1. This sequence will be non-descending. So the number of array a and b that fulfills this condition is equal to number of ways of constructing non-descending sequence of length 2m and each element is between 1 and n. In order to do this, we can use stick and stone technique. Consider xi as "how many times we use number i in the sequence". So we will have this equality: `x1 + x2 + .. + xn = 2m`, where `x1, x2, .., xn >= 0`. The number of solution is therefore C(2m + n - 1, n - 1).

# Problem D
Notice that if we can make the minimax at least x, we can surely make the minimax at least x - 1. This calls for binary search solution. We fix the minimax value and we convert each array to binary. The i-th bit is on if this number is larger than or equal to the minimax. After that, we need to find two array whose XOR is (2^m - 1). Notice there are only 2^m values, so we can just try all pairs.
