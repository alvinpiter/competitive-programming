#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000
#define MOD 1000000007

int bit[MAXN + 3];

void update(int idx, int val) {
    while (idx <= MAXN) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int N, P[MAXN + 3];
vector<int> uniqP;
LL factorial[MAXN + 3];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
        uniqP.push_back(P[i]);
    }

    //normalize P
    sort(uniqP.begin(), uniqP.end());
    uniqP.resize(distance(uniqP.begin(), unique(uniqP.begin(), uniqP.end())));

    for (int i = 1; i <= N; i++)
        P[i] = (lower_bound(uniqP.begin(), uniqP.end(), P[i]) - uniqP.begin()) + 1;

    //initially all numbers are available
    memset(bit, 0, sizeof(bit));
    for (int i = 1; i <= N; i++)
        update(i, 1);

    factorial[0] = 1;
    for (int i = 1; i <= N; i++)
        factorial[i] = (factorial[i - 1] * i)%MOD;

    LL order = 0;
    for (int i = 1; i <= N; i++) {
        int cntBelow = query(P[i] - 1);

        order += factorial[N - i] * cntBelow;
        order %= MOD;

        //P[i] is already used
        update(P[i], -1);
    }

    order = (order + 1)%MOD;

    printf("%lld\n", order);
}
