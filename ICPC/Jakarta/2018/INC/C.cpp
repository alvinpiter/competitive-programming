#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MAXLG 17

int N, Q, ages[MAXN + 3];
vector<int> uniqueAges;
vector<int> children[MAXN + 3];
LL BIT[MAXN + 3]; //Binary indexed tree
int depth[MAXN + 3], P[MAXN + 3][MAXLG + 3]; //LCA
vector<tuple<int, int, int> > queriesEndAt[MAXN + 3], queriesLCAAt[MAXN + 3]; //Process the queries offline. (l, r, queryIndex). l and r are normalized.
LL answer[MAXN + 3];

void updateBIT(int idx, LL val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

LL queryBIT(int idx) {
    LL result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

void initDepth(int u) {
    for (auto v: children[u]) {
        depth[v] = depth[u] + 1;

        initDepth(v);
    }
}

void initLCA(int root) {
    depth[root] = 0;
    initDepth(root);

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            P[i][lg] = P[i][lg - 1] == -1 ? -1 : P[P[i][lg - 1]][lg - 1];
        }
    }
}

int LCA(int u, int v) {
    if (depth[u] > depth[v])
        swap(u, v);

    int diff = depth[v] - depth[u];
    for (int i = 0; i <= MAXLG; i++) {
        if (diff & (1 << i))
            v = P[v][i];
    }

    if (u == v)
        return u;

    for (int lg = MAXLG; lg >= 0; lg--) {
        if (P[u][lg] != P[v][lg]) {
            u = P[u][lg];
            v = P[v][lg];
        }
    }

    return P[u][0];
}

int normalizeLB(int age) {
    return (lower_bound(uniqueAges.begin(), uniqueAges.end(), age) - uniqueAges.begin()) + 1;
}

int normalizeUB(int age) {
    return (upper_bound(uniqueAges.begin(), uniqueAges.end(), age) - uniqueAges.begin());
}

//Populate answer
void traverse(int u) {
    updateBIT(normalizeLB(ages[u]), ages[u]);

    for (auto query: queriesEndAt[u]) {
        int l = get<0>(query), r = get<1>(query), idx = get<2>(query);
        answer[idx] += queryBIT(r) - queryBIT(l - 1);
    }

    for (auto query: queriesLCAAt[u]) {
        int l = get<0>(query), r = get<1>(query), idx = get<2>(query);
        answer[idx] -= 2 * (queryBIT(r) - queryBIT(l - 1));
    }

    for (auto v: children[u])
        traverse(v);

    updateBIT(normalizeLB(ages[u]), -ages[u]);
}

int main() {
    memset(P, -1, sizeof(P));
    memset(BIT, 0, sizeof(answer));
    memset(answer, 0, sizeof(answer));

    scanf("%d%d", &N, &Q);

    for (int i = 1; i <= N; i++) {
        scanf("%d", &ages[i]);
        uniqueAges.push_back(ages[i]);
    }

    for (int i = 1; i <= N - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        children[x].push_back(y);
        P[y][0] = x;
    }

    int root;
    for (int i = 1; i <= N; i++) {
        if (P[i][0] == -1)
            root = i;
    }

    initLCA(root);

    //Unique-fy the ages
    sort(uniqueAges.begin(), uniqueAges.end());
    uniqueAges.resize(distance(uniqueAges.begin(), unique(uniqueAges.begin(), uniqueAges.end())));

    for (int i = 1; i <= Q; i++) {
        int a, b, l, r;

        scanf("%d%d%d%d", &a, &b, &l, &r);

        int lca = LCA(a, b);
        if (ages[lca] >= l && ages[lca] <= r)
            answer[i] += ages[lca];

        queriesEndAt[a].push_back(make_tuple(normalizeLB(l), normalizeUB(r), i));
        queriesEndAt[b].push_back(make_tuple(normalizeLB(l), normalizeUB(r), i));
        queriesLCAAt[lca].push_back(make_tuple(normalizeLB(l), normalizeUB(r), i));
    }

    traverse(root);

    for (int i = 1; i <= Q; i++)
        printf("%lld\n", answer[i]);
}

/*
9 7
1000000000 1000000000 1000000000 12 45 34 22 10 11
1 2
1 3
2 4
2 5
3 6
3 7
5 8
5 9
2 3 1000000000 1000000000
4 9 11 12
4 9 9 50
7 8 0 1000000000
6 7 22 23
4 9 10 1000000000
2 9 11 12
*/
