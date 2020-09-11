#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Observation:
Suppose we have a sequence Si and a number x. If we convert all Si to Si - x and
take the sum and the result is < 0, then the average of Si is less than x.
Proof:
(S1 - x) + (S2 - x) + .. + (Sn - x) < 0
(S1 + S2 + .. + Sn) - x*n < 0
(S1 + S2 + .. + Sn)/n < x

The strategy to solve this problem is by keep lowering the upperbound of average milk
production from remaining machine. Suppose we guess the average milk production from
remaining machine is x. Let's convert each Mi to Mi - x. If there is sum of prefix and
sum of suffix which is < 0, then by the above observation, we know that the upperbound
of the answer is x. Otherwise, x is the lowerbound of the answer.

How do we find prefix and suffix whose sum is < 0? We first calculate the sum of all Mi - x,
and then we substract the maximum sum of consecutive elements from it, or mathematically:
sum(Mi - x) - maxSum(Mi - x).

Notice that the above formula will decrease as x increase and vice versa, which is a hint
for binary search solution.
*/

int main() {
    freopen("sabotage.in", "r", stdin);
    freopen("sabotage.out", "w", stdout);

    int N, M[MAXN + 3];

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> M[i];
    }

    double lo = 0, hi = 10000, mid;
    for (int rep = 1; rep <= 50; rep++) {
        mid = (lo + hi)/2;

        double sum = 0;
        for (int i = 1; i <= N; i++)
            sum += (M[i] - mid);

        double currentSum = M[2] - mid;
        double maxSum = currentSum;
        for (int i = 3; i < N; i++) {
            currentSum = max(currentSum + M[i] - mid, M[i] - mid);
            maxSum = max(maxSum, currentSum);
        }

        if (sum - maxSum < 0)
            hi = mid;
        else
            lo = mid;
    }

    printf("%.3lf\n", mid);
}
