#include<bits/stdc++.h>
using namespace std;
#define HOOF 0
#define PAPER 1
#define SCISSOR 2
#define MAXN 100000
#define MAXK 20

int id(char c) {
    if (c == 'H') return HOOF;
    if (c == 'P') return PAPER;
    if (c == 'S') return SCISSOR;
}

//return 1 if a wins against b, 0 otherwise
int judge(int a, int b) {
    if (a == HOOF && b == SCISSOR) return 1;
    if (a == PAPER && b == HOOF) return 1;
    if (a == SCISSOR && b == PAPER) return 1;

    return 0;
}

int N, K, dp[MAXN + 3][MAXK + 3][3], fj[MAXN + 3];

/*
maximum number of games that can be win out of the first i games
where we can change hand `rem` times and current hand is `hand`
*/
int solve(int i, int rem, int hand) {
    if (i == 0)
        return 0;

    if (dp[i][rem][hand] != -1)
        return dp[i][rem][hand];

    int unchanged = judge(hand, fj[i]) + solve(i - 1, rem, hand);
    int changed = 0;
    for (int newHand = 0; newHand < 3; newHand++) {
        if (newHand != hand && rem > 0) {
            changed = max(changed, judge(newHand, fj[i]) + solve(i - 1, rem - 1, newHand));
        }
    }

    return dp[i][rem][hand] = max(changed, unchanged);
}

int main() {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    cin >> N >> K;
    for(int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        fj[i] = id(c);
    }

    memset(dp, -1, sizeof(dp));
    cout << max(solve(N, K, HOOF), max(solve(N, K, PAPER), solve(N, K, SCISSOR))) << endl;
}
