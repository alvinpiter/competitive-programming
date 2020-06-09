#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define NOT_VISITED 0
#define ACTIVE 1
#define VISITED 2

/*
Notice the shuffle will form a graph where every vertex has 1 out edge.
A vertex will always have a cow in it if it is part of cycle.
*/

int N, nxt[MAXN + 3], stat[MAXN + 3];
bool isPartOfCycle[MAXN + 3];
vector<int> cycleOrigins;

void DFS(int u) {
    stat[u] = ACTIVE;

    if (stat[nxt[u]] == ACTIVE) {
        cycleOrigins.push_back(nxt[u]);
    } else if (stat[nxt[u]] == NOT_VISITED) {
        DFS(nxt[u]);
    }

    stat[u] = VISITED;
}

void DFS2(int u) {
    isPartOfCycle[u] = true;
    if (isPartOfCycle[nxt[u]] == false)
        DFS2(nxt[u]);
}

int main() {
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> nxt[i];

    memset(stat, NOT_VISITED, sizeof(stat));
    for (int u = 1; u <= N; u++) {
        if (stat[u] == NOT_VISITED)
            DFS(u);
    }

    memset(isPartOfCycle, false, sizeof(isPartOfCycle));
    for (auto u: cycleOrigins) {
        DFS2(u);
    }

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        if (isPartOfCycle[i])
            answer += 1;
    }

    cout << answer << endl;
}
