#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000
#define WHITE 0
#define BLACK 1

/*
Notice that color 2's neighbor must be either 1 or 3, while color 1's and color 3's neighbor must be color 2.
If the graph is bicolorable, then all black node can be set as color 2 and white node can be set as either 1 or 3. Or vice versa.

dp[i][j] -> Is it possible to get j nodes for color 2 out of the first i connected components
sol[i][j] -> true if we take white as color 2, false if we take black as color 2 for state (i, j)
*/

int n, m, n1, n2, n3, bicolor[MAXN + 3], ccIndex[MAXN + 3], numCC, cntColor[MAXN + 3][2], ans[MAXN + 3];
vector<int> adj[MAXN + 3];
bool dp[MAXN + 3][MAXN + 3], sol[MAXN + 3][MAXN + 3];

bool checkBipartite(int u, int currentColor) {
    bicolor[u] = currentColor;
    cntColor[numCC][currentColor] += 1;
    ccIndex[u] = numCC;

    bool bipartite = true;
    for (auto v: adj[u]) {
        if (bicolor[v] == -1) {
            bipartite = bipartite && checkBipartite(v, 1 - currentColor);
        } else {
            if (bicolor[v] == bicolor[u])
                bipartite = false;
        }
    }

    return bipartite;
}

//Traverse dp state
void color2(int cc, int rem) {
    if (cc == 0)
        return;

    if (sol[cc][rem] == true) {
        //take whites as color 2
        for (int i = 1; i <= n; i++) {
            if (ccIndex[i] == cc && bicolor[i] == WHITE)
                ans[i] = 2;
        }

        color2(cc - 1, rem - cntColor[cc][WHITE]);
    } else {
        //take blacks as color 3
        for (int i = 1; i <= n; i++) {
            if (ccIndex[i] == cc && bicolor[i] == BLACK)
                ans[i] = 2;
        }

        color2(cc - 1, rem - cntColor[cc][BLACK]);
    }
}

void color13() {
    for (int i = 1; i <= n; i++) {
        if (ans[i] == -1) {
            if (n1 > 0) {
                ans[i] = 1;
                n1 -= 1;
            } else {
                ans[i] = 3;
                n3 -= 1;
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    scanf("%d%d%d", &n1, &n2, &n3);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(bicolor, -1, sizeof(bicolor));
    memset(cntColor, 0, sizeof(cntColor));
    numCC = 0;

    for (int i = 1; i <= n; i++) {
        if (bicolor[i] == -1) {
            numCC += 1;

            bool bipartite = checkBipartite(i, WHITE);
            if (!bipartite) {
                printf("NO\n");
                return 0;
            }
        }
    }

    dp[0][0] = true;
    for (int i = 1; i <= numCC; i++) {
        for (int j = 0; j <= n2; j++) {
            dp[i][j] = false;

            //try white
            if (cntColor[i][WHITE] <= j && dp[i - 1][j - cntColor[i][WHITE]]) {
                dp[i][j] = true;
                sol[i][j] = true;
            }

            //try black
            if (cntColor[i][BLACK] <= j && dp[i - 1][j - cntColor[i][BLACK]]) {
                dp[i][j] = true;
                sol[i][j] = false;
            }
        }
    }

    if (dp[numCC][n2] == false) {
        printf("NO\n");
        return 0;
    }

    memset(ans, -1, sizeof(ans));

    color2(numCC, n2);
    color13();

    printf("YES\n");
    for (int i = 1; i <= n; i++)
        printf("%d", ans[i]);

    printf("\n");
}
