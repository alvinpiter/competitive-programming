# Problem C
Assume the gcd of the sequence is g, then we can convert the sequence into:
g(a1' + a2' + ... + ak') = n
Notice that g must be divisor of n and a1' + a2' + .. + ak' must be at least (k * k + k)/2 because the sequence must be strictly increasing. Try every value of g and take the maximal. To construct the sequence, the first k - 1 numbers would be g, 2g, 3g, .. and the last number is the left over.
