#include<bits/stdc++.h>
using namespace std;
#define MAXN 500
#define MOD 1000000007

/*
Naive way to solve this is by defining a recursive function solve(r1, c1, r2, c2) which calculates
number of paths from (r1, c1) to (r2, c2) such that the path is palindrome. The complexity of this method
is O(N^4).

The other way is to define a function solve(layer, r1, r2) which calculates number of paths with length
2 * layer + 1 that starts from r1 and ends at r2, where it the (layer + 1)-th cell is on the diagonal.
The complexity is now O(N^3). We need dp flying table to optimize memory usage.

Why the second function works? because from the state (layer, r1, r2), we can deduce the value
of c1 and c2. In other words, state (layer, r1, r2) is just simplification of state (r1, c1, r2, c2).
*/

int N;
long long int dp[2][MAXN + 3][MAXN + 3];
char grid[MAXN + 3][MAXN + 3];

int main() {
    freopen("palpath.in", "r", stdin);
    freopen("palpath.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cin >> grid[i][j];
    }

    //base case
    int t = 0;
    for (int i = 1; i <= N; i++)
        dp[t][i][i] = 1;

    //fill dp layer by layer
    for (int layer = 1; layer <= N - 1; layer++) {
        t = 1 - t;

        //iterate over layer above main diagonal
        for (int r1 = N - layer, c1 = 1; r1 >= 1; r1--, c1++) {
            //iterate over its pair on the other side
            for (int r2 = N, c2 = 1 + layer; c2 <= N; r2--, c2++) {
                dp[t][r1][r2] = 0;

                if (r1 > r2 || c1 > c2 || grid[r1][c1] != grid[r2][c2])
                    continue;

                //iterate over neighbors of (r1, c1) and neighbors of (r2, c2)
                for (int dr1 = 0; dr1 <= 1; dr1++) {
                    for (int dc1 = 0; dc1 <= 1; dc1++) {
                        for (int dr2 = -1; dr2 <= 0; dr2++) {
                            for (int dc2 = -1; dc2 <= 0; dc2++) {
                                if (dr1 != dc1 && dr2 != dc2 && grid[r1 + dr1][c1 + dc1] == grid[r2 + dr2][c2 + dc2]) {
                                    dp[t][r1][r2] += dp[1 - t][r1 + dr1][r2 + dr2];
                                    dp[t][r1][r2] %= MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    cout << dp[t][1][N] << endl;
}
