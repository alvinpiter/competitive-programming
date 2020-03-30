#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, K, numUni[MAXN + 3];
bool isUni[MAXN + 3];
vector<int> adj[MAXN + 3];
LL answer;

void DFS1(int u, int prv) {
    numUni[u] = (isUni[u] ? 1 : 0);
    for (auto v: adj[u]) {
        if (v != prv) {
            DFS1(v, u);
            numUni[u] += numUni[v];
        }
    }
}

void DFS2(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            answer += min(numUni[v], 2 * K - numUni[v]);
            DFS2(v, u);
        }
    }
}

int main() {
    cin >> N >> K;

    memset(isUni, false, sizeof(isUni));
    for (int i = 1; i <= 2 * K; i++) {
        int u;
        cin >> u;

        isUni[u] = true;
    }

    for (int i = 1; i < N; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(numUni, 0, sizeof(numUni));
    DFS1(1, 1);

    answer = 0;
    DFS2(1, 1);

    cout << answer << endl;
}
