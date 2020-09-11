#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MOD 998244353

/*
Use contribution technique.

For each number, process its digits from right (least significant one). Assume we are now at k-th digit from right.
We will find out the contribution of this digit to the answer. To do so, we try to merge current number with number with length l and calculate position of current digit in the result.
*/

int n, cnt[12]; //cnt[i] -> number of strings whose length is i
LL p10[20];
string a[MAXN + 3];

int main() {
    cin >> n;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt[(int) a[i].length()] += 1;
    }

    p10[0] = 1;
    for (int i = 1; i < 20; i++)
        p10[i] = (p10[i - 1] * 10)%MOD;

    LL answer = 0;
    for (int i = 1; i <= n; i++) {
        int curLen = (int) a[i].length();
        for (int j = curLen - 1, k = 1; j >= 0; j--, k++) {
            int d = (a[i][j] - '0');

            //try merging current number with string with length l
            for (int l = 1; l <= 10; l++) {
                LL c1, c2;
                if (l < k) {
                    c1 = (p10[k - 1 + l] * d * cnt[l])%MOD; //f(current, other)
                    c2 = c1;                                //f(other, current)
                }

                if (l >= k) {
                    c1 = (p10[k - 1 + k    ] * d * cnt[l])%MOD; //f(other, current)
                    c2 = (p10[k - 1 + k - 1] * d * cnt[l])%MOD; //f(current, other)
                }

                answer = (answer + c1 + c2)%MOD;
            }
        }
    }

    cout << answer << endl;
}
