#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
dp[i] -> earliest time cow i is finished being milked.
dp[i] = t[i] + max(dp[j]), where j is the cow has to be milked before i

Answer is max(dp[i]);
*/

int N, M, T[MAXN + 3], dp[MAXN + 3];
vector<int> revConstraint[MAXN + 3];

int solve(int u) {
    if (dp[u] != -1)
        return dp[u];

    int result = T[u];
    for (auto v: revConstraint[u]) {
        result = max(result, T[u] + solve(v));
    }

    return dp[u] = result;
}

int main() {
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> T[i];

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;

        revConstraint[b].push_back(a);
    }

    memset(dp, -1, sizeof(dp));

    int answer = 0;
    for (int i = 1; i <= N; i++)
        answer = max(answer, solve(i));

    cout << answer << endl;
}
