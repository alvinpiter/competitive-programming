#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define MAXK 100

/*
dpPrefix[i][j] = Is it possible to make cells 1..i obey rules 1..j
dpSuffix[i][j] = Is it possible to make cells i..N obey rules j..K
*/

string S;
int N, K, C[MAXK + 3], prefixWhite[MAXN + 3], prefixBlack[MAXN + 3];
int dpPrefix[MAXN + 3][MAXK + 3], dpSuffix[MAXN + 3][MAXK + 3], canBeWhite[MAXN + 3], canBeBlack[MAXN + 3];

int main() {
    cin >> S;
    N = S.length();

    cin >> K;
    for (int i = 1; i <= K; i++)
        cin >> C[i];

    //Populate prefixWhite and prefixBlack
    prefixWhite[0] = 0;
    for (int i = 1; i <= N; i++) {
        prefixWhite[i] = prefixWhite[i - 1] + (S[i - 1] == '_' ? 1 : 0);
        prefixBlack[i] = prefixBlack[i - 1] + (S[i - 1] == 'X' ? 1 : 0);
    }

    //Populate dpPrefix
    for (int j = 1; j <= K; j++)
        dpPrefix[0][j] = false;

    for (int i = 1; i <= N; i++)
        dpPrefix[i][0] = (prefixBlack[i] == 0);

    dpPrefix[0][0] = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= K; j++) {
            bool white = dpPrefix[i - 1][j];
            bool black;

            if (i < C[j])
                black = false;
            else if (i == C[j])
                black = (prefixWhite[i] - prefixWhite[i - C[j]] == 0 && dpPrefix[i - C[j]][j - 1]);
            else
                black = (prefixWhite[i] - prefixWhite[i - C[j]] == 0 && S[i - C[j] - 1] != 'X' && dpPrefix[i - C[j] - 1][j - 1]);

            if (S[i - 1] == '_')
                dpPrefix[i][j] = white;
            else if (S[i - 1] == 'X')
                dpPrefix[i][j] = black;
            else
                dpPrefix[i][j] = (white || black);
        }
    }

    //Populate dpSuffix
    for (int j = 1; j <= K; j++)
        dpSuffix[N + 1][j] = false;

    for (int i = 1; i <= N; i++)
        dpSuffix[i][K + 1] = (prefixBlack[N] - prefixBlack[i - 1] == 0);

    dpSuffix[N + 1][K + 1] = true;
    for (int i = N; i >= 1; i--) {
        for (int j = K; j >= 1; j--) {
            bool white = dpSuffix[i + 1][j];
            bool black;

            if (i + C[j] - 1 > N)
                black = false;
            else if (i + C[j] - 1 == N)
                black = (prefixWhite[i + C[j] - 1] - prefixWhite[i - 1] == 0 && dpSuffix[i + C[j]][j + 1]);
            else
                black = (prefixWhite[i + C[j] - 1] - prefixWhite[i - 1] == 0 && S[(i + C[j]) - 1] != 'X' && dpSuffix[i + C[j] + 1][j + 1]);

            if (S[i - 1] == '_')
                dpSuffix[i][j] = white;
            else if (S[i - 1] == 'X')
                dpSuffix[i][j] = black;
            else
                dpSuffix[i][j] = (white || black);
        }
    }

    //Populate canBeWhite[i]
    memset(canBeWhite, 0, sizeof(canBeWhite));
    for (int i = 1; i <= N; i++) {
        if (S[i - 1] == 'X')
            continue;

        bool possible = false;
        for (int j = 0; j <= K; j++) {
            if (dpPrefix[i - 1][j] && dpSuffix[i + 1][j + 1])
                possible = true;
        }

        //Note: prefix sum is not needed, but i do it anyway to make it similar with canBeBlack
        if (possible) {
            canBeWhite[i] += 1;
            canBeWhite[i + 1] -= 1;
        }
    }

    //Populate canBeBlack[i]
    memset(canBeBlack, 0, sizeof(canBeBlack));
    for (int j = 1; j <= K; j++) {
        for (int i = 1; i <= N; i++) {
            //Out of range
            if (i + C[j] - 1 > N)
                break;

            //The left and the right are forced to be black
            if ((i > 1 && S[(i - 1) - 1] == 'X') || ((i + C[j] - 1 < N && S[(i + C[j]) - 1] == 'X')))
                continue;

            //There is a forced white cell within the range
            if (prefixWhite[i + C[j] - 1] - prefixWhite[i - 1] > 0)
                continue;

            int possibleLeft = ((i == 1 && j == 1) || dpPrefix[i - 2][j - 1]);
            int possibleRight = ((i + C[j] - 1 == N && j == K) || dpSuffix[i + C[j] + 1][j + 1]);

            if (possibleLeft && possibleRight) {
                canBeBlack[i] += 1;
                canBeBlack[i + C[j]] -= 1;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        canBeWhite[i] += canBeWhite[i - 1];
        canBeBlack[i] += canBeBlack[i - 1];
    }

    for (int i = 1; i <= N; i++) {
        if (canBeWhite[i] > 0 && canBeBlack[i] > 0)
            cout << "?";
        else if (canBeWhite[i] > 0)
            cout << "_";
        else if (canBeBlack[i] > 0)
            cout << "X";
    }
    cout << endl;
}
