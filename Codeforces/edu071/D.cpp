#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000
#define MOD 998244353
#define pii pair<int, int>

int n;
vector<pii> pairs;
vector<int> cnt;
LL fact[MAXN + 3];

bool cmpFirst(pii a, pii b) { return a.first < b.first; }
bool cmpSecond(pii a, pii b) { return a.second < b.second; }

LL countSortedByFirst() {
    sort(pairs.begin(), pairs.end(), cmpFirst);

    vector<int> cnt;

    int cons = 1;
    for (int i = 1; i < pairs.size(); i++) {
        if (pairs[i].first == pairs[i - 1].first)
            cons += 1;
        else {
            cnt.push_back(cons);
            cons = 1;
        }
    }
    cnt.push_back(cons);

    LL result = 1;
    for (auto c: cnt) result = (result * fact[c])%MOD;

    return result;
}

LL countSortedBySecond() {
    sort(pairs.begin(), pairs.end(), cmpSecond);

    vector<int> cnt;

    int cons = 1;
    for (int i = 1; i < pairs.size(); i++) {
        if (pairs[i].second == pairs[i - 1].second)
            cons += 1;
        else {
            cnt.push_back(cons);
            cons = 1;
        }
    }
    cnt.push_back(cons);

    LL result = 1;
    for (auto c: cnt) result = (result * fact[c])%MOD;

    return result;
}

LL countSortedByBoth() {
    sort(pairs.begin(), pairs.end());

    vector<int> cnt;

    int cons = 1;
    for (int i = 1; i < pairs.size(); i++) {
        if (pairs[i].second < pairs[i - 1].second)
            return 0;

        if (pairs[i] == pairs[i - 1])
            cons += 1;
        else {
            cnt.push_back(cons);
            cons = 1;
        }
    }
    cnt.push_back(cons);

    LL result = 1;
    for (auto c: cnt) result = (result * fact[c])%MOD;

    return result;
}

int main() {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);

        pairs.push_back({a, b});
    }

    LL sortedByFirst = countSortedByFirst();
    LL sortedBySecond = countSortedBySecond();
    LL sortedByBoth = countSortedByBoth();
    LL bad = ((sortedByFirst + sortedBySecond)%MOD - sortedByBoth + MOD) % MOD;
    LL all = fact[n];

    cout << (all - bad + MOD)%MOD << endl;
}
