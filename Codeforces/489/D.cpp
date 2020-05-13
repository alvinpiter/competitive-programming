#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 3e18
#define MAXN 200000

/*
Categorize numbers into two categories:
* Good number, which is number that is > 1
* Bad number, which is number that is = 1

The observation is that the number of good number in solution is not that many.

Imagine there is a solution with length l. We want to find the upperbound for l.

Maximum possible product is k * l * 10^8 <= l * 10^13
Assume all the good number is 2 (smallest possible). 2^l = l*10^13. l is about log(10^13).
*/

int main() {
    //nxtGood[i] -> smallest j (j > i) such that a[j] is good number

    int n, k, a[MAXN + 3], nxtGood[MAXN + 3];

    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    nxtGood[n] = n + 1;
    for (int i = n - 1; i >= 1; i--) {
        if (a[i + 1] == 1)
            nxtGood[i] = nxtGood[i + 1];
        else
            nxtGood[i] = i + 1;
    }

    int answer = 0;

    //brute force the starting position of an answer
    for (int i = 1; i <= n; i++) {
        LL product = 1;
        LL sum = 0;

        int j = i;
        while (j <= n && product < INF/a[j]) {
            product *= a[j];
            sum += a[j];

            if (product % k == 0) {
                int targetSum = product/k;
                int diffSum = targetSum - sum;
                int ones = nxtGood[j] - j - 1;

                if (diffSum >= 0 && ones >= diffSum)
                    answer += 1;
            }

            sum += (nxtGood[j] - j - 1);
            j = nxtGood[j];
        }
    }

    cout << answer << endl;
}
