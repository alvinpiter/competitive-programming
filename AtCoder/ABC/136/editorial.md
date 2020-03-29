# Problem D
consR[i] -> How many R to the left of index i (including i)
consL[i] -> how many L to the right of index i (including i)

Notice that after 10^100 moves, all children will be at index i or i + 1, where S[i] = 'R' and S[i] = 'L'.
The number of children at index i would be (consR[i]/2 + 1) + consL[i + 1]/2 and number of children at index i + 1 would be consR[i]/2 + (consL[i + 1] + 1)/2. The reason is because children located to the right of index i and at even distance from i will end up at i and all children located to the left of index i (including i) and at even distance from i will end up at i. The same logic can be applied to count the answer for index i + 1.

# Problem E
Let the final sequence be a1 + k1, a2 + k2, a3 + k3, .., an + kn.

Observation 1: k1 + k2 + .. + kn must be 0 and sum of positive ki must be the same with sum of negative ki
Proof: In one operation, we increase some ki by 1 and decrease some kj by 1 (i != j), so the total must be 0 and number of positive and negative operation is the same.

Observation 2: The final gcd must be divisor of a1 + a2 + .. + an.
Proof: Assume the gcd is g. g divides every ai + ki, so g must also divide sum of ai + ki. From the observation 1, we know sum of ki is 0, hence g divides a1 + a2 + .. + an.

Observation 3: Assume we already choose some gcd g. Now let's take a look at remainder of every a when divided by g, let them be r1, r2, .., rn. WLOG, let r is sorted non-decreasingly. It is optimal to choose some prefix of r as the sum of negative operations and choose some prefix of r as the sum of positive operations.
Proof: We can proof by exchange argument. Let's first take out two elements ri and rj (ri > rj). From the rest of the r's, let's take prefix of length m and as sum of negative operations and the suffix as sum of positive operations. Then put ri on the prefix set and put rj on suffix set. We want to show that by exchanging ri and rj the difference of the sum of positive and negative operations is the same.

sumNeg' = (sumNeg - ri) + rj
sumPos' = (sumPos - (g - rj)) + (g - ri)

sumPos' - sumNeg' = sumPos - g + rj + g - ri - sumNeg + ri - rj
sumPos' - sumNeg' = sumPos - sumNeg

With those 3 observations we can construct an algorithm:
* Choose some g (There are at most sqrt(N * maxA)).
* Check if we can perform operations on A to achieve gcd equals g with some operations. (Use observation 3 here).
* Don't forget to handle corner case, that is when we don't have to perform operation on the array.
