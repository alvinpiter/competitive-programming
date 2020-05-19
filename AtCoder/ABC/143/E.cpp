#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300
#define INF 1e12

int N, M, L, Q;
LL d1[MAXN + 3][MAXN + 3], d2[MAXN + 3][MAXN + 3];

int main() {
    cin >> N >> M >> L;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            d1[i][j] = d2[i][j] = INF;
    }

    for (int i = 1; i <= M; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        d1[a][b] = d1[b][a] = c;
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++)
                d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (d1[i][j] <= L)
                d2[i][j] = 1;
        }
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);
            }
        }
    }

    cin >> Q;
    for (int i = 1; i <= Q; i++) {
        int s, t;
        cin >> s >> t;

        if (d2[s][t] < INF)
            cout << d2[s][t] - 1 << endl;
        else
            cout << -1 << endl;
    }
}
