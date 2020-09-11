#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, K, parent[MAXN + 3], sz[MAXN + 3];
vector<int> friends[MAXN + 3], blocks[MAXN + 3];

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void unionSet(int u, int v) {
    int pu = findSet(u), pv = findSet(v);

    if (pu == pv) return;

    parent[pu] = pv;
    sz[pv] += sz[pu];
}

int main() {
    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    for (int i = 1; i <= M; i++) {
        int a, b;
        cin >> a >> b;

        friends[a].push_back(b);
        friends[b].push_back(a);

        unionSet(a, b);
    }

    for (int i = 1; i <= K; i++) {
        int a, b;
        cin >> a >> b;

        blocks[a].push_back(b);
        blocks[b].push_back(a);
    }

    for (int i = 1; i <= N; i++) {
        int componentSize = sz[findSet(i)];
        int numBlocks = 0, numFriends = friends[i].size();

        for (auto b: blocks[i]) {
            if (isSameSet(i, b))
                numBlocks += 1;
        }

        cout << (componentSize - 1) - numFriends - numBlocks << " ";
    }
    cout << endl;
}
