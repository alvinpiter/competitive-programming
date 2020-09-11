# Problem E

# Problem F
Notice that the after k insert operations the function will become f(x) = |x - a1| + |x - a2| + .. + |x - ak| + sum(b1..bk).
In order for f to be minimum, x must be the median of a1..ak. We can create a data structure for median finding using two sets, one for storing the first n/2 smallest a and one for storing the last n/2 highest a.
