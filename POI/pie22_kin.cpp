#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000000

int N, M, movie[MAXN + 3], score[MAXN + 3];
LL tree[4 * MAXN + 3], lazy[4 * MAXN + 3];
vector<int> pos[MAXN + 3];

LL evaluate(int node) {
    return tree[node] + lazy[node];
}

void pushDown(int node, int l, int r) {
    if (l != r) {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void pullUp(int node, int l, int r) {
    tree[node] = max(evaluate(2 * node), evaluate(2 * node + 1));
}

LL query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return 0;

    if (l >= le && r <= ri)
        return evaluate(node);

    pushDown(node, l, r);

    int m = (l + r)/2;
    LL result = max(
        query(2 * node, l, m, le, ri),
        query(2 * node + 1, m + 1, r, le, ri)
    );

    pullUp(node, l, r);

    return result;
}

LL query(int le, int ri) {
    return query(1, 1, N, le, ri);
}

void update(int node, int l, int r, int le, int ri, int val) {
    if (r < le || l > ri)
        return;

    if (l >= le && r <= ri) {
        lazy[node] += val;
        return;
    }

    pushDown(node, l, r);

    int m = (l + r)/2;
    update(2 * node, l, m, le, ri, val);
    update(2 * node + 1, m + 1, r, le, ri, val);

    pullUp(node, l, r);
}

void update(int le, int ri, int val) {
    update(1, 1, N, le, ri, val);
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%d", &movie[i]);

    for (int i = 1; i <= M; i++)
        scanf("%d", &score[i]);

    memset(tree, 0, sizeof(tree));
    memset(lazy, 0, sizeof(lazy));

    LL answer = 0;
    for (int i = 1; i <= N; i++) {
        int currentMovie = movie[i];

        if (pos[currentMovie].size() == 1) {
            int p = pos[currentMovie][0];
            update(1, p, -2 * score[currentMovie]);
        } else if (pos[currentMovie].size() == 2) {
            int p1 = pos[currentMovie][0]; //the closer one
            int p2 = pos[currentMovie][1]; //the farther one
            update(1, p1, -2 * score[currentMovie]);
            update(1, p2, +score[currentMovie]);
        }

        pos[currentMovie].insert(pos[currentMovie].begin(), i);
        if (pos[currentMovie].size() > 2) pos[currentMovie].pop_back();

        update(1, i, score[currentMovie]);

        answer = max(answer, query(1, i));
    }

    printf("%lld\n", answer);
}

/*
9 4
2 3 1 1 4 1 2 4 1
5 3 6 6
*/
