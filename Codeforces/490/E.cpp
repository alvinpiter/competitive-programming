#include<bits/stdc++.h>
using namespace std;
#define MAXN 5000

/*
Find number of node which does not have indegree in condensed graph.
*/

int n, m, s;
bool reachable[MAXN + 3], visited[MAXN + 3];
vector<int> adj[MAXN + 3];
stack<int> st;

//mark vertices that are reachable from s
void dfs1(int u) {
    reachable[u] = true;
    for (auto v: adj[u]) {
        if (reachable[v] == false)
            dfs1(v);
    }
}

//order unreachable vertices in non-increasing finishing time
void dfs2(int u) {
    visited[u] = true;
    for (auto v: adj[u]) {
        if (visited[v] == false)
            dfs2(v);
    }

    st.push(u);
}

int main() {
    cin >> n >> m >> s;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
    }

    memset(reachable, false, sizeof(reachable));
    memset(visited, false, sizeof(visited));

    dfs1(s);

    for (int i = 1; i <= n; i++) {
        if (!reachable[i] && !visited[i])
            dfs2(i);
    }

    int answer = 0;
    while (!st.empty()) {
        int u = st.top(); st.pop();

        //implicitly add edge from s to u
        if (!reachable[u]) {
            answer += 1;
            dfs1(u);
        }
    }

    cout << answer << endl;
}
