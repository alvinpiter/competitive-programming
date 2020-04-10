#include<bits/stdc++.h>
using namespace std;
#define MAXN 200

int N, M, answer;
bool isImpossible[MAXN + 3][MAXN + 3];

int main() {
    cin >> N >> M;

    memset(isImpossible, false, sizeof(isImpossible));
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        isImpossible[u][v] = isImpossible[v][u] = true;
    }

    answer = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            for (int k = j + 1; k <= N; k++) {
                if (!isImpossible[i][j] && !isImpossible[i][k] && !isImpossible[j][k])
                    answer += 1;
            }
        }
    }

    cout << answer << endl;
}
