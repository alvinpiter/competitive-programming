#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 5000
#define MAXK 5000
#define DEBUG true

int N, K, V;
LL a[MAXN + 3], sumA;
bool dp[MAXN + 3][MAXK + 3], sol[MAXN + 3][MAXK + 3], taken[MAXN + 3]; //dp[n][k] -> is there subset of the first n numbers such that its sum equals to k modulo K.
vector<pair<int, pair<int, int> > > answer;

void generateSubset(int n, int k) {
    if (n == 0)
        return;

    if (sol[n][k]) {
        taken[n] = true;
        generateSubset(n - 1, (k - a[n]%K + K)%K);
    } else {
        generateSubset(n - 1, k);
    }
}

int main() {
    cin >> N >> K >> V;

    sumA = 0;
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
        sumA += a[i];
    }

    if (V > sumA) {
        cout << "NO\n";
        return 0;
    }

    memset(dp, false, sizeof(dp));
    memset(sol, true, sizeof(sol));
    dp[0][0] = true;

    for (int n = 1; n <= N; n++) {
        for (int k = 0; k < K; k++) {
            if (dp[n - 1][k]) {
                dp[n][k] = true;
                sol[n][k] = false;
            }

            int prevK = (k - a[n]%K + K)%K;
            if (dp[n - 1][prevK]) {
                dp[n][k] = true;
                sol[n][k] = true;
            }
        }
    }

    if (dp[N][V%K] == false) {
        cout << "NO\n";
        return 0;
    }

    memset(taken, false, sizeof(taken));
    generateSubset(N, V%K);

    int X = 0, Y;
    for (int i = 1; i <= N; i++) {
        if (taken[i]) {
            X = i;
            break;
        }
    }

    if (X == 0) {
        int from = 1;
        int to = 2;
        int cnt = a[from]/K + (a[from]%K == 0 ? 0 : 1);

        if (cnt > 0) {
            answer.push_back({cnt, {from, to}});
            a[to] += a[from];
            a[from] = 0;
        }

        X = 1;
    }

    Y = (X == 1 ? 2 : 1);

    for (int from = 1; from <= N; from++) {
        if (from == X || taken[from] == false) continue;

        LL cnt = a[from]/K + (a[from]%K == 0 ? 0 : 1);

        if (cnt == 0) continue;

        a[X] += a[from];
        a[from] = 0;
        answer.push_back({cnt, {from, X}});
    }

    for (int from = 1; from <= N; from++) {
        if (from == Y || taken[from] == true) continue;

        LL cnt = a[from]/K + (a[from]%K == 0 ? 0 : 1);

        if (cnt == 0) continue;

        a[Y] += a[from];
        a[from] = 0;
        answer.push_back({cnt, {from, Y}});
    }

    if (X != 0 && a[X] > V) {
        LL diff = a[X] - V;
        LL cnt = diff/K;

        a[X] -= diff;
        a[Y] += diff;
        answer.push_back({cnt, {X, Y}});
    }

    if (X != 0 && a[X] < V) {
        LL diff = V - a[X];
        LL cnt = diff/K;

        a[X] += diff;
        a[Y] -= diff;
        answer.push_back({cnt, {Y, X}});
    }

    cout << "YES\n";
    for (auto a: answer)
        cout << a.first << " " << a.second.first << " " << a.second.second << endl;
}
