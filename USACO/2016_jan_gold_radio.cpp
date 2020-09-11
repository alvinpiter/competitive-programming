#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

pair<int, int> move(pair<int, int> pos, char dir) {
    if (dir == 'N')
        return {pos.first, pos.second + 1};
    if (dir == 'E')
        return {pos.first + 1, pos.second};
    if (dir == 'S')
        return {pos.first, pos.second - 1};
    if (dir == 'W')
        return {pos.first - 1, pos.second};
}

int dist(pair<int, int> p1, pair<int, int> p2) {
    return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second);
}

int N, M, fx, fy, bx, by, dp[MAXN + 3][MAXN + 3];
pair<int, int> fj[MAXN + 3], bessie[MAXN + 3];

int solve(int i, int j) {
    if (i == N && j == M)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    int best = 2e9 + 3;

    //fj moves forward, bessie stays
    if (i < N) {
        best = min(best, dist(fj[i + 1], bessie[j]) + solve(i + 1, j));
    }

    //bessie moves forward, fj stays
    if (j < M) {
        best = min(best, dist(fj[i], bessie[j + 1]) + solve(i, j + 1));
    }

    //fj and bessie moves forward
    if (i < N && j < M) {
        best = min(best, dist(fj[i + 1], bessie[j + 1]) + solve(i + 1, j + 1));
    }

    return dp[i][j] = best;
}

int main() {
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    cin >> N >> M >> fx >> fy >> bx >> by;

    fj[0] = {fx, fy};
    bessie[0] = {bx, by};

    for (int i = 1; i <= N; i++) {
        char dir;
        cin >> dir;

        fj[i] = move(fj[i - 1], dir);
    }

    for (int i = 1; i <= M; i++) {
        char dir;
        cin >> dir;

        bessie[i] = move(bessie[i - 1], dir);
    }

    memset(dp, -1, sizeof(dp));

    cout << solve(0, 0) << endl;
}
