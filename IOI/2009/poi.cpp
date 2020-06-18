#include<bits/stdc++.h>
using namespace std;
#define MAXN 2000

int N, T, P, mat[MAXN + 3][MAXN + 3], cntSolve[MAXN + 3];
pair<int, pair<int, int> > scores[MAXN + 3];

bool cmpScore(pair<int, pair<int, int> > a, pair<int, pair<int, int> > b) {
    if (a.first != b.first)
        return a.first > b.first;
    else {
        if (a.second.first != b.second.first)
            return a.second.first > b.second.first;
        else
            return a.second.second < b.second.second;
    }
}

int main() {
    cin >> N >> T >> P;

    memset(cntSolve, 0, sizeof(cntSolve));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= T; j++) {
            cin >> mat[i][j];

            if (mat[i][j] == 1)
                cntSolve[j] += 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        int score = 0;
        int numSolve = 0;
        for (int j = 1; j <= T; j++) {
            if (mat[i][j] == 1) {
                score += (N - cntSolve[j]);
                numSolve += 1;
            }
        }

        scores[i] = {score, {numSolve, i}};
    }

    sort(scores + 1, scores + N + 1, cmpScore);

    for (int i = 1; i <= N; i++) {
        if (scores[i].second.second == P) {
            cout << scores[i].first << " " << i << endl;
            return 0;
        }
    }
}
