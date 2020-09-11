#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000
#define MAXLG 20

/*
Define balance as number of opening bracket minus number of closing bracket.

A bracket sequence is regular if the balance is 0 and the minimum of balance of each index is non negative.
*/

string s;
int n, balance[MAXN + 3], st[MAXN + 3][MAXLG + 3], lg2[MAXN + 3];
vector<int> pos[2 * MAXN + 3];

int queryST(int l, int r) {
    int sz = r - l;

    return min(
        st[l][lg2[sz]],
        st[r - (1 << lg2[sz])][lg2[sz]]
    );
}

int main() {
    lg2[1] = 0;
    for (int i = 2, cur = 1; i <= MAXN; i++) {
        if (cur * 2 == i) {
            lg2[i] = lg2[i - 1] + 1;
            cur *= 2;
        } else {
            lg2[i] = lg2[i - 1];
        }
    }

    cin >> s;

    n = (int) s.length();

    balance[0] = 0;
    pos[0 + MAXN].push_back(0);

    for (int i = 1; i <= n; i++) {
        balance[i] = balance[i - 1] + (s[i - 1] == '(' ? 1 : -1);
        pos[balance[i] + MAXN].push_back(i);
    }

    //sparse table base case
    st[n][0] = balance[n];
    for (int i = 1; i < n; i++)
        st[i][0] = min(balance[i], balance[i + 1]);

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i + (1 << lg) <= n; i++) {
            st[i][lg] = min(st[i][lg - 1], st[i + (1 << (lg - 1))][lg - 1]);
        }
    }

    int best = 0;
    int cnt = 1;
    for (int i = 1; i <= n; i++) {
        //find last index where minBalance is 0
        int lo = i, hi = n, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;

            int minBalance = queryST(i, mid) - balance[i - 1];

            if (minBalance >= 0)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (hi < i)
            continue;

        //find last index where balance is equal to balance[i - 1]
        auto ptr = lower_bound(pos[balance[i - 1] + MAXN].begin(), pos[balance[i - 1] + MAXN].end(), hi + 1);

        if (ptr == pos[balance[i - 1] + MAXN].begin() || *(--ptr) < i)
            continue;

        int len = *ptr - i + 1;

        if (len > best) {
            best = len;
            cnt = 1;
        } else if (len == best) {
            cnt += 1;
        }
    }

    cout << best << " " << cnt << endl;
}
