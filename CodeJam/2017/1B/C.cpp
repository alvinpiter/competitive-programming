#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e12
#define MAXN 100

/*
Algorithm:
* Run APSP algorithm to get shortest path between every pair of towns.
* Construct a new graph that has the same vertices with the original graph. Connect two vertex i and j if we can go from i to j using horse j. The weight of the edge equals to time needed to go from i to j.
* Run APSP on the new graph.
*/

int main() {
    int T, N, Q, E[MAXN + 3], S[MAXN + 3];
    LL d1[MAXN + 3][MAXN + 3];
    double d2[MAXN + 3][MAXN + 3];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d", &N, &Q);
        for (int i = 1; i <= N; i++)
            scanf("%d%d", &E[i], &S[i]);

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                scanf("%lld", &d1[i][j]);

                if (d1[i][j] == -1)
                    d1[i][j] = (i == j ? 0 : INF);
            }
        }

        //APSP on original graph
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    d1[i][j] = min(d1[i][j], d1[i][k] + d1[k][j]);
                }
            }
        }

        //construct new graph
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                d2[i][j] = INF;

                if (d1[i][j] <= E[i])
                    d2[i][j] = d1[i][j]/(S[i] * 1.0);
            }
        }

        //APSP on new graph
        for (int k = 1; k <= N; k++) {
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++)
                    d2[i][j] = min(d2[i][j], d2[i][k] + d2[k][j]);
            }
        }

        printf("Case #%d:", cases);
        for (int i = 1; i <= Q; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            printf(" %.7lf", d2[u][v]);
        }
        printf("\n");
    }
}
