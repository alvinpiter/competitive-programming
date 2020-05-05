#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000

/*
depthXor[d] -> XOR of elements at depth d. Element is described with binary number. a is 2^0, b is 2^1, etc.
*/

int N, M, tin[MAXN + 3], tout[MAXN + 3], dfsTime;
vector<int> children[MAXN + 3];
vector<pair<int, int> > depthXor[MAXN + 3];
char S[MAXN + 3];

void DFS(int u, int depth) {
    ++dfsTime;
    tin[u] = dfsTime;

    int currentChar = (1 << (S[u - 1] - 'a'));
    if (depthXor[depth].empty())
        depthXor[depth].push_back({tin[u], currentChar});
    else
        depthXor[depth].push_back({tin[u], depthXor[depth].back().second ^ currentChar});

    for (auto child: children[u]) {
        DFS(child, depth + 1);
    }

    tout[u] = dfsTime;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 2; i <= N; i++) {
        int p;
        scanf("%d", &p);

        children[p].push_back(i);
    }

    scanf("%s", S);

    dfsTime = 0;
    DFS(1, 1);

    for (int q = 1; q <= M; q++) {
        int v, h;
        scanf("%d%d", &v, &h);

        int p1 = lower_bound(depthXor[h].begin(), depthXor[h].end(), make_pair(tin[v], -1)) - depthXor[h].begin();
        int p2 = lower_bound(depthXor[h].begin(), depthXor[h].end(), make_pair(tout[v], -1)) - depthXor[h].begin();

        if (p2 == depthXor[h].size() || depthXor[h][p2].first > tout[v])
            p2 -= 1;

        if (p2 < 0) {
            printf("Yes\n");
            continue;
        }

        int xorr = depthXor[h][p2].second;
        if (p1 > 0)
            xorr ^= depthXor[h][p1 - 1].second;

        int cnt = 0;
        for (int i = 0; i < 26; i++) {
            if (xorr & (1 << i))
                cnt += 1;
        }

        if (cnt <= 1)
            printf("Yes\n");
        else
            printf("No\n");
    }
}
