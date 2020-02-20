#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXK 10
#define MOD 1000000007
#define LL long long int

/*
dp1[h][k] -> how many binary tree with height h such that there are exactly k nodes at level h
dp2[h] -> how many binary tree with height h
*/

LL dp1[MAXN + 3][MAXK + 3], dp2[MAXN + 3], sumDp2[MAXN + 3];
int H, K;

//Precompute dp2 and sumDp2
void precompute() {
    dp2[0] = sumDp2[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        dp2[i] = ((2 * dp2[i - 1] * sumDp2[i - 1])%MOD - (dp2[i - 1] * dp2[i - 1])%MOD + MOD)%MOD;
        sumDp2[i] = (sumDp2[i - 1] + dp2[i])%MOD;
    }
}

LL solve(int h, int k) {
    if (h == 1)
        return (k == 1 ? 1 : 0);

    if (dp1[h][k] != -1)
        return dp1[h][k];

    LL result = 0;

    //Case 1: left subtree has height h - 1, and right subtree has height at most h - 2
    result = (result + solve(h - 1, k) * sumDp2[h - 2])%MOD;

    //Case 2: right subtree has height h - 1, and left subtree has height at most h - 2
    result = (result + solve(h - 1, k) * sumDp2[h - 2])%MOD;

    //Case 3: left and right subtree has height h - 1.
    for (int c = 1; c < k; c++)
        result = (result + solve(h - 1, c) * solve(h - 1, k - c))%MOD;

    return dp1[h][k] = result;
}

int main() {
    precompute();

    cin >> H >> K;

    memset(dp1, -1, sizeof(dp1));
    cout << solve(H, K) << endl;
}
