#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

/*
before[i][j] => How many numbers from 1 to j appears before i in the initial sequence.
*/
int T, N, pos[MAXN + 3], before[MAXN + 3][MAXN + 3], dp[MAXN + 3][MAXN + 3];

/*
Get the index of `who`, when numbers from a to b already taken.
*/
int getIndex(int who, int a, int b) {
    return (pos[who] - (before[who][b] - before[who][a - 1]));
}

/*
solve(i, j) => Minimum cost to construct sequence i..j
*/
int solve(int i, int j) {
    if (i == j)
        return pos[i];

    if (dp[i][j] != -1)
        return dp[i][j];

    int first = solve(i, j - 1) + (j - i + 1) * getIndex(j, i, j - 1);
    int second = solve(i + 1, j) + (j - i + 1) * getIndex(i, i + 1, j);

    return dp[i][j] = min(first, second);
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;
        for (int i = 1; i <= N; i++) {
            int number;
            cin >> number;

            pos[number] = i;
        }

        for (int i = 1; i <= N; i++) {
            before[i][0] = 0;
            for (int j = 1; j <= N; j++)
                before[i][j] = before[i][j - 1] + (pos[j] < pos[i] ? 1 : 0);
        }

        memset(dp, -1, sizeof(dp));
        cout << solve(1, N) << endl;
    }
}
