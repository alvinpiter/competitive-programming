/*
Define a random variable `Beauty` as the number of painted node in the tree.
Define a random variable `painted_i` which equals to 1 if node i is painted, 0 otherwise.

The two RV correlates as follows:
E(Beauty) = E(painted_1) + E(painted_2) + ... + E(painted_n)

Simplifying, we get:
E(Beauty) = (probability_node_1_is_painted) + (probability_node_2_is_painted) + ...

We will calculate probability_node_i_is_painted.
p_node_i_painted = 1 - p_node_i_not_painted
p_node_i_painted = 1 - ((1 - p_node_i_painted_by_A) * (1 - p_node_i_painted_by_B))
p_node_i_painted = p_node_i_painted_by_A + p_node_i_painted_by_B - p_node_A_painted_by_A*p_node_B_painted_by_B

p_node_i_painted_by_A can is the number of nodes j in subtree i such that (depth[j] - depth[i])%A = 0.
*/

#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

int T, N, A, B;
int cntModA[MAXN + 3], cntModB[MAXN + 3];
vector<int> children[MAXN + 3];
double answer;

void DFS(int u, int depth) {
    int prvCntModA = cntModA[depth%A];
    int prvCntModB = cntModB[depth%B];

    cntModA[depth%A] += 1;
    cntModB[depth%B] += 1;
    for (auto c: children[u]) {
        DFS(c, depth + 1);
    }

    int currCntModA = cntModA[depth%A] - prvCntModA;
    int currCntModB = cntModB[depth%B] - prvCntModB;

    double pA = (1.0 * currCntModA)/N;
    double pB = (1.0 * currCntModB)/N;

    answer += (pA + pB - pA * pB);
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%d%d", &N, &A, &B);

        //reset everything
        for (int i = 0; i <= N; i++) {
            children[i].clear();
            cntModA[i] = cntModB[i] = 0;
        }

        for (int i = 2; i <= N; i++) {
            int p;
            scanf("%d", &p);

            children[p].push_back(i);
        }

        answer = 0;
        DFS(1, 0);

        printf("Case #%d: %.7lf\n", cases, answer);
    }
}
