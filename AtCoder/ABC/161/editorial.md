# Problem A, B
Easy

# Problem C
If N >= K, N will be downgraded into N%K. After this, just take the minimum between N and K - N.

# Problem D
Generate all lunlun numbers using recursion.

# Problem E
Assume we are currently at day i. Let a and b be the maximum number of works before day i and maximum number of works after day i respectively. If a + b < K, then he is bound to work at day i.

# Problem F
Divide the value of K into two cases:
* K is divisor of N -> There are only sqrt(N) possibilities, simulate them all.
* K is not divisor of N -> It means that the final N would be N%K (because N - x * K will not be divisible by K). If we want N%K == 1, then K must be divisor of (N - 1). There are also sqrt(N) possibilities, simulate them all.

The edge case is when N = 2. The answer is 1.
