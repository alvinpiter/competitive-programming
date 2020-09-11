#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000

/*
Observation: Minimize the depth of each node.
Proof: Imagine a node at some depth, it will contribute salary to all its ancestors. Hence it's better
to minimize the depth.
*/

int N, depth[MAXN + 3], cntDepth[MAXN + 3], answer;
bool done[MAXN + 3];
vector<int> whoWants[MAXN + 3];

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        int num, b;
        scanf("%d", &num);

        for (int j = 1; j <= num; j++) {
            scanf("%d", &b);
            whoWants[b].push_back(i);
        }
    }

    answer = 1e9;
    for (int root = 1; root <= N; root++) {
        for (int i = 0; i <= N; i++) {
            cntDepth[i] = 0;
            done[i] = false;
        }

        depth[root] = 0;
        cntDepth[depth[root]] += 1;
        done[root] = true;

        int maxDepth = 0;
        int cntDone = 1;

        queue<int> q;
        q.push(root);

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v: whoWants[u]) {
                if (!done[v]) {
                    depth[v] = depth[u] + 1;
                    cntDepth[depth[v]] += 1;
                    done[v] = true;

                    maxDepth = max(maxDepth, depth[v]);
                    cntDone += 1;

                    q.push(v);
                }
            }
        }

        if (cntDone != N)
            continue;

        int sumSalaryAtCurrentDepth = cntDepth[maxDepth];
        int sumSalary = sumSalaryAtCurrentDepth;

        for (int d = maxDepth - 1; d >= 0; d--) {
            sumSalaryAtCurrentDepth += cntDepth[d];
            sumSalary += sumSalaryAtCurrentDepth;
        }

        answer = min(answer, sumSalary);
    }

    printf("%d\n", answer);
}
