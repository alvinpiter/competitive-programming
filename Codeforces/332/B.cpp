#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int main() {
    int N, M;
    vector<int> pos[MAXN + 3];
    vector<int> answer;

    scanf("%d%d", &N, &M);

    for (int i = 1; i <= N; i++) {
        int f;
        scanf("%d", &f);

        pos[f].push_back(i);
    }

    bool isAmbiguous = false;
    for (int i = 1; i <= M; i++) {
        int b;
        scanf("%d", &b);

        if (pos[b].empty()) {
            printf("Impossible\n");
            return 0;
        }

        if (pos[b].size() > 1) {
            isAmbiguous = true;
        }

        answer.push_back(pos[b][0]);
    }

    if (isAmbiguous) {
        printf("Ambiguity\n");
    } else {
        printf("Possible\n");
        for (auto a: answer)
            printf("%d ", a);
        printf("\n");
    }
}
