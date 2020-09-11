#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

/*
For each index i, we would like to know all j (j >= i) such that i and j will be a pair in some palindrome.
To do this, we can treat i as first number in palindrome, as second number in palindrome, and so on.

Assume i's pairs are j1, j2, j3, .., jk
Notice that j1, j2, j3 will form an arithmetic progression with difference 2.

Some num[j] may be smaller than num[i]. So we will separate the solution into two parts:
* Calculating the cases where num[j] < num[i]
* Calculating the cases where num[j] > num[i]

We can do it by sorting the pairs {num[i], i} and maintain some BITs.
*/

int n, k;
pair<int, int> numbers[MAXN + 3];

void update(LL bit[], int idx, int val) {
    while (idx <= n) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

LL query(LL bit[], int idx) {
    LL result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

LL rsq(LL bit[], int l, int r) {
    return query(bit, r) - query(bit, l - 1);
}

LL getAnswer() {
    LL sumOdd[MAXN + 3], sumEven[MAXN + 3], cntOdd[MAXN + 3], cntEven[MAXN + 3];

    memset(sumOdd, 0, sizeof(sumOdd));
    memset(sumEven, 0, sizeof(sumEven));
    memset(cntOdd, 0, sizeof(cntOdd));
    memset(cntEven, 0, sizeof(cntEven));

    LL answer = 0;
    for (int i = 1; i <= n; i++) {
        int number = numbers[i].first;
        int idx = numbers[i].second;

        int miniPalindromeIndex = max(1, idx + k - n);
        int maxiPalindromeIndex = min((k + 1)/2, idx);

        if (miniPalindromeIndex <= maxiPalindromeIndex) {
            int miniIdx = idx + k - 2 * maxiPalindromeIndex + 1;
            int maxiIdx = idx + k - 2 * miniPalindromeIndex + 1;

            if (miniIdx % 2 == 0) {
                answer += number * rsq(cntEven, miniIdx, maxiIdx) - rsq(sumEven, miniIdx, maxiIdx);
            } else {
                answer += number * rsq(cntOdd, miniIdx, maxiIdx) - rsq(sumOdd, miniIdx, maxiIdx);
            }
        }

        if (idx % 2 == 0) {
            update(sumEven, idx, number);
            update(cntEven, idx, 1);
        } else {
            update(sumOdd, idx, number);
            update(cntOdd, idx, 1);
        }
    }

    return answer;
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        numbers[i] = {a, i};
    }

    sort(numbers + 1, numbers + n + 1);

    LL answer = getAnswer();

    reverse(numbers + 1, numbers + n + 1);

    answer += abs(getAnswer());

    printf("%lld\n", answer);
}
