#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXP 7
#define LL long long int

int N, P, K;
int positionScore[MAXN + 3][MAXP + 3];
pair<int, int> audienceScore[MAXN + 3];
LL dp[MAXN + 3][(1 << MAXP) + 3];

int countOnBit(int mask) {
    int count = 0;
    for (int i = 0; i <= MAXP; i++)
        count += ((1 << i) & mask) ? 1 : 0;

    return count;
}

//solve(n, mask) => maximum score reachable if we are considering the first n people and set of available position is denoted as mask
LL solve(int n, int mask) {
    if (n == 0) {
        if (mask == 0)
            return 0;
        else
            return -1e18;
    }

    if (dp[n][mask] != -1)
        return dp[n][mask];

    int playerIndex = audienceScore[n].second;
    int playerAudienceScore = audienceScore[n].first;
    int numAudience = (N - n) - (P - countOnBit(mask));

    //Current player is assigned as audience.
    LL option1 = solve(n - 1, mask) + (numAudience < K ? playerAudienceScore : 0);

    //Try assiging current player to available positions
    LL option2 = 0;
    for (int i = 0; i < P; i++) {
        if (mask & (1 << i)) {
            option2 = max(option2, positionScore[playerIndex][i] + solve(n - 1, mask ^ (1 << i)));
        }
    }

    return dp[n][mask] = max(option1, option2);
}

int main() {
    scanf("%d%d%d", &N, &P, &K);
    for (int i = 1; i <= N; i++) {
        int s;
        scanf("%d", &s);

        audienceScore[i] = {s, i};
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < P; j++)
            scanf("%d", &positionScore[i][j]);
    }

    sort(audienceScore + 1, audienceScore + N + 1);

    memset(dp, -1, sizeof(dp));
    printf("%lld\n", solve(N, (1 << P) - 1));
}
