# Problem E
Person whose starting time is D will get blocked by i-th roadwork if this following condition is fulfilled:
Si - Xi <= D < Ti - Xi
If there are many roadwork fulfills the inequality, choose the one with smallest X.

Assume we are currently processing person whose starting time is D, We need to know which roadwork will block it. We can do line sweep algorithm and maintain the values of X that might block the current person. There are two main events here:
* Event where a new roadwork is introduced (i.e. at S - X)
* Event where a roadwork is done (i.e. at T - X)

# Problem F
Let's choose some A and B and analyze the pattern.

0, A, A - B, 2A - B, 2A - 2B, 3A - 2B, 3A - 3B, ...

Let's say A - B = C:

0, C + B, C, 2C + B, 2C, 3C + B, 3C, ...

Observe that we will reach the destination after odd number of steps. Assume the number of steps taken is 2k + 1, for k >= 0. Because the destination is in N - 1, we have (k + 1)C + B = N - 1. We can rewrite the pattern:

0, (N - 1) - kC, C, (N - 1) - (k - 1)C, 2C, (N - 1) - (k - 2)C, 3C, ..., (N - 1) - C, kC, N - 1

Notice that for a fixed C, path for k and k + 1 is very similar. For example let's say C = 2.

If k = 3, the path would be:
0, (N - 1) - 3C, C, (N - 1) - 2C, 2C, (N - 1) - C, 3C, N - 1

If k = 4, the path would be:
0, (N - 1) - 4C, C, (N - 1) - 3C, 2C, (N - 1) - 2C, 3C, (N - 1) - C, 4C, N - 1.

The only difference is (N - 1) - 4C and 4C. Or in general term, the difference between path k and k + 1 is (N - 1) - (k + 1)C and (k + 1)C.

Since kC < N - 1, number of pairs of k and C is O(N log N).

Some caveats:
A must be larger than 1.
B must be larger than 0.
This costs me too much WA. Too much.
