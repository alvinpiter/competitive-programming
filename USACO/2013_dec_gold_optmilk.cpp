#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 40000

struct Node {
    LL best[2][2];
    Node() {
        best[0][0] = best[0][1] = best[1][0] = best[1][1] = 0;
    }
    Node(int x) {
        best[0][0] = best[0][1] = best[1][0] = 0;
        best[1][1] = x;
    }
};

Node merge(Node node1, Node node2) {
    Node result;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result.best[i][j] = 0;
            for (int m1 = 0; m1 < 2; m1++) {
                for (int m2 = 0; m2 < 2; m2++) {
                    if (m1 == 1 && m2 == 1)
                        continue;

                    result.best[i][j] = max(result.best[i][j], node1.best[i][m1] + node2.best[m2][j]);
                }
            }
        }
    }

    return result;
}

int N, D;
Node tree[4 * MAXN + 3];
LL answer;

void update(int node, int l, int r, int idx, int val) {
    if (r < idx || l > idx)
        return;

    if (l == r) {
        tree[node] = Node(val);
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);

    tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    freopen("optmilk.in", "r", stdin);
    freopen("optmilk.out", "w", stdout);

    scanf("%d%d", &N, &D);
    for (int i = 1; i <= N; i++) {
        int M;
        scanf("%d", &M);

        update(1, 1, N, i, M);
    }

    answer = 0;
    for (int i = 1; i <= D; i++) {
        int idx, m;
        scanf("%d%d", &idx, &m);
        update(1, 1, N, idx, m);

        LL best = max(
            max(tree[1].best[0][0], tree[1].best[0][1]),
            max(tree[1].best[1][0], tree[1].best[1][1])
        );

        answer += best;
    }

    printf("%lld\n", answer);
}
