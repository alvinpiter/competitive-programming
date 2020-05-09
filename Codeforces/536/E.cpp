#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e15
#define MAXN 100000
#define MAXM 200

struct Envelope {
    int id, endTime, nextTime, coin;
    Envelope(int _id, int _endTime, int _nextTime, int _coin): id(_id), endTime(_endTime), nextTime(_nextTime), coin(_coin) {}
    friend bool operator<(Envelope a, Envelope b) {
        if (a.coin != b.coin)
            return a.coin < b.coin;

        if (a.nextTime != b.nextTime)
            return a.nextTime < b.nextTime;
    }
};

int n, m, k, s[MAXN + 3], t[MAXN + 3], d[MAXN + 3], w[MAXN + 3], bestEnvelope[MAXN + 3];
LL dp[MAXN + 3][MAXM + 3];
vector<Envelope> events[MAXN + 3];

//Min number of point reachable fromtime i to n if currently Alice can disturb j times
LL solve(int i, int j) {
    if (i == n + 1)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (bestEnvelope[i] == -1)
        return dp[i][j] = solve(i + 1, j);

    LL take = w[bestEnvelope[i]] + solve(d[bestEnvelope[i]] + 1, j);
    LL skip = (j > 0 ? solve(i + 1, j - 1) : INF);

    return dp[i][j] = min(take, skip);
}

int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= k; i++) {
        scanf("%d%d%d%d", &s[i], &t[i], &d[i], &w[i]);

        events[s[i]].push_back(Envelope{i, t[i], d[i], w[i]});
    }

    priority_queue<Envelope> pq;

    memset(bestEnvelope, -1, sizeof(bestEnvelope));
    for (int t = 1; t <= n; t++) {
        for (auto event: events[t])
            pq.push(event);

        while (!pq.empty() && pq.top().endTime < t)
            pq.pop();

        if (!pq.empty())
            bestEnvelope[t] = pq.top().id;
    }

    memset(dp, -1, sizeof(dp));
    printf("%lld\n", solve(1, m));
}
