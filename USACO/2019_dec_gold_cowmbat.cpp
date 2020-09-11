#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 100000
#define MAXC 26

/*
The solution to this problem can be broken to a few parts:
* Finding the minimum cost to convert character to another character.
  Model the alphabets as graph, where each alphabet is a node.
  The cost of converting one character to another character is the edge weight between those nodes.
  Converting one character to another can then be solved by finding shortest path between the two.
  We can apply Floyd-Warshall algorithm for this
* Given a substring i..j, what is the cost for converting all the characters into somme character?
  This can be done with prefix sum. Define prefixCost[i][c] as the minimum cost to convert the first
  i characters to be character c.
* Finding optimal way to convert the string into combos
  Define dp[j][c] as the minimum cost to convert the first j characters into a combo, given that
  the last character is c. The formula:
  dp[j][c] = min(dp[j - 1][c] + letterCost[S[j]][c], prefixCost[j][c] - prefixCost[j - k][c] + min(dp[j - k][c']))

  The transition is:
    * Either take exactly K same character or
    * Take more than K same character
*/

int N, M, K, S[MAXN + 3];
int letterCost[MAXC + 3][MAXC + 3], prefixCost[MAXN + 3][MAXC + 3];
int dp[MAXN + 3][MAXC + 3];

int main() {
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++) {
        char c;
        cin >> c;

        S[i] = (c - 'a');
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            cin >> letterCost[i][j];
        }
    }

    //Floyd-Warshall algorithm, finding the minimum cost to convert a character to another character
    for (int k = 0; k < M; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                letterCost[i][j] = min(letterCost[i][j], letterCost[i][k] + letterCost[k][j]);
            }
        }
    }

    //Calculating prefixCost;
    for (int c = 0; c < M; c++) {
        prefixCost[0][c] = 0;
        for (int i = 1; i <= N; i++) {
            prefixCost[i][c] = prefixCost[i - 1][c] + letterCost[S[i]][c];
        }
    }

    //base case
    for (int i = 0; i < K; i++) {
        for (int c = 0; c < M; c++)
            dp[i][c] = (i == 0 ? 0 : INF);
    }

    for (int i = K; i <= N; i++) {
        for (int c = 0; c < M; c++) {
            int mini = INF;
            for (int cp = 0; cp < M; cp++)
                mini = min(mini, dp[i - K][cp]);

            dp[i][c] = min(dp[i - 1][c] + letterCost[S[i]][c], mini + (prefixCost[i][c] - prefixCost[i - K][c]));
        }
    }

    int answer = INF;
    for (int c = 0; c < M; c++)
        answer = min(answer, dp[N][c]);

    cout << answer << endl;
}
