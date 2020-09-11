#include<bits/stdc++.h>
using namespace std;
#define MAXN 20

int N, B, mat[MAXN + 3][MAXN + 3], dp[(1 << MAXN) + 3];
vector<pair<int, int> > bonusesAt[MAXN + 3];
vector<int> sumBonusesAt[MAXN + 3];

//If currently 'idx' cows already assigned and the total score is 'score', how much is the bonus?
int calculateBonus(int idx, int score) {
    int lo = 0, hi = bonusesAt[idx].size() - 1, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (bonusesAt[idx][mid].first <= score)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    if (lo == 0)
        return 0;
    else
        return sumBonusesAt[idx][lo - 1];
}

int main() {
    freopen("dec.in", "r", stdin);
    freopen("dec.out", "w", stdout);

    cin >> N >> B;
    for (int i = 0; i < B; i++) {
        int k, p, a;
        cin >> k >> p >> a;

        bonusesAt[k].push_back({p, a});
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> mat[i][j];
    }

    //precalculate bonuses
    for (int idx = 1; idx <= N; idx++) {
        if (bonusesAt[idx].empty())
            continue;

        sort(bonusesAt[idx].begin(), bonusesAt[idx].end());
        sumBonusesAt[idx].push_back(bonusesAt[idx][0].second);

        for (int i = 1; i < bonusesAt[idx].size(); i++)
            sumBonusesAt[idx].push_back(sumBonusesAt[idx].back() + bonusesAt[idx][i].second);
    }

    dp[0] = 0;
    for (int mask = 1; mask < (1 << N); mask++) {
        int cntOnBit = 0;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i))
                cntOnBit += 1;
        }

        int best = 0;

        int curr = cntOnBit - 1;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                int score = mat[i][curr] + dp[mask ^ (1 << i)];

                //calcuateBonus can be put outside (line 75), we will maximize dp[mask] first then give bonus.
                best = max(best, score + calculateBonus(cntOnBit, score));
            }
        }

        dp[mask] = best;
    }

    cout << dp[(1 << N) - 1] << endl;
}
