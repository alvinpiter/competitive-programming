#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000000
#define MAXLG 19

/*
nxt2[i][lg] -> next 2^lg uncovered module if we start covering from module i
*/

int N, S, nxt[MAXN + 3][MAXLG + 2], bestPos;
LL K, pos[MAXN + 3], sumV[MAXN + 3], bestScore;
vector<int> answer;

LL calculateScore(int i) {
    int j = i;
    for (int lg = 0; lg <= MAXLG && j <= N; lg++) {
        if (S & (1 << lg)) {
            j = nxt[j][lg];
        }
    }

    return sumV[j - 1] - sumV[i - 1];
}

int main() {
    scanf("%d%d%lld", &N, &S, &K);

    pos[1] = 0;
    pos[N + 1] = 1e18;
    for (int i = 2; i <= N; i++) {
        int d;
        scanf("%d", &d);

        pos[i] = pos[i - 1] + d;
    }

    sumV[0] = 0;
    for (int i = 1; i <= N; i++) {
        int v;
        scanf("%d", &v);

        sumV[i] = sumV[i - 1] + v;
    }

    for (int i = 1; i <= N; i++) {
        int p1 = lower_bound(pos + 1, pos + N + 1, pos[i] + K) - pos;

        if (pos[p1] > pos[i] + K)
            p1 -= 1;

        int p2 = lower_bound(pos + 1, pos + N + 1, pos[p1] + K) - pos;

        if (pos[p2] == pos[p1] + K)
            p2 += 1;

        nxt[i][0] = p2;
    }

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            int j = nxt[i][lg - 1];

            if (j == N + 1)
                nxt[i][lg] = j;
            else
                nxt[i][lg] = nxt[nxt[i][lg - 1]][lg - 1];
        }
    }

    bestScore = 0;
    for (int l = 1; l <= N; l++) {
        LL score = calculateScore(l);
        if (score > bestScore) {
            bestScore = score;
            bestPos = l;
        }
    }

    int cur = bestPos;
    for (int rep = 1; rep <= S && cur <= N; rep++) {
        int p = lower_bound(pos + 1, pos + N + 1, pos[cur] + K) - pos;
        if (pos[p] > pos[cur] + K)
            p -= 1;

        answer.push_back(p);

        cur = nxt[cur][0];
    }

    printf("%d\n", (int) answer.size());
    for (int i = 0; i < (int) answer.size(); i++) {
        if (i > 0) printf(" ");
        printf("%d", answer[i]);
    }
    printf("\n");
}
