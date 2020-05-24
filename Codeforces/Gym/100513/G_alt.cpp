#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

/*
First we make the first segment (index 1..k) to be negative.
It's better to decrease right most elements first.

Observation:
For every subsequent segments, we only need at most 1 decrease operation to make the sum < 0.

Proof:
Assume segment l..r sum is < 0
Now we want to process segment (l+1)..(r+1).
Sum of (l+1)..(r+1) is sum(l..r) - a[l] + a[r + 1].

There are two cases:
a[l] >= a[r + 1] -> We don't have to do anything
a[l] < a[r + 1] -> We can decrease a[r + 1] to a[l]

In both cases, we only need at most 1 decrease operation. QED.
*/

int n, k, a[MAXN + 3], mini, answer;

int main() {
    scanf("%d%d", &n, &k);

    mini = MAXN;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        mini = min(mini, a[i]);
    }

    int currentSum = 0;
    for (int i = 1; i <= k; i++)
        currentSum += a[i];

    answer = 0;
    if (currentSum >= 0) {
        int toDecrease = currentSum + 1;

        for (int i = k; i >= 1 && toDecrease > 0; i--) {
            int canTake = a[i] - mini;
            int take = min(canTake, toDecrease);

            toDecrease -= take;

            a[i] -= take;
            currentSum -= take;
            answer += take;
        }
    }

    for (int i = k + 1; i <= n; i++) {
        currentSum += a[i];
        currentSum -= a[i - k];

        if (currentSum >= 0) {
            int take = currentSum + 1;

            a[i] -= take;
            currentSum -= take;
            answer += take;
        }
    }

    printf("%d\n", answer);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
}
