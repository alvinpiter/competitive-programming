# Problem F
Observation: Assume we have a clique. If we sorted the values, than value at index i will be multiple of value at index i-1.

Define cnt[i] -> how many times number i occurs
Define dp[i] -> Maximum size of a clique where the smallest number is i.

dp[i] = cnt[i] + max(dp[2 * i], dp[3 * i], .. dp[k * i])
