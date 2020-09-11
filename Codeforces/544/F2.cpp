#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

//numCC is number of connected components if we exclude all edges that is from node 1
int N, M, D, inDegree[MAXN + 3], numCC, ccId[MAXN + 3];
bool visited[MAXN + 3], oneCantVisit[MAXN + 3]; //oneCantVisit[i] -> true if edge from 1 to i is removed
queue<int> Q; //For BFS
vector<int> adj[MAXN + 3];
vector<pair<int, int> > answer;

void DFS(int u) {
    visited[u] = true;
    ccId[u] = numCC;
    for (auto v: adj[u]) {
        if (v != 1 && visited[v] == false)
            DFS(v);
    }
}

void countNumberOfConnectedComponents() {
    memset(visited, false, sizeof(visited));

    numCC = 0;
    for (int i = 2; i <= N; i++) {
        if (visited[i] == false) {
            numCC += 1;
            DFS(i);
        }
    }
}

void initializeBFSStartingPosition() {
    int connectionsLeft = D;
    bool alreadyConnectedToCC[MAXN + 3]; //alreadyConnectedToCC[i] = true if node 1 is already connected to connected component with id i

    memset(visited, false, sizeof(visited));
    visited[1] = true;

    Q.push(1);

    //Connect to all connected components
    for (auto v: adj[1]) {
        if (!alreadyConnectedToCC[ccId[v]]) {
            answer.push_back({1, v});

            visited[v] = true;
            Q.push(v);

            alreadyConnectedToCC[ccId[v]] = true;
            connectionsLeft -= 1;
        }
    }

    //Connect to all remaining nodes
    for (auto v: adj[1]) {
        if (connectionsLeft == 0)
            break;

        if (visited[v])
            continue;

        answer.push_back({1, v});
        visited[v] = true;
        Q.push(v);

        alreadyConnectedToCC[ccId[v]] = true;
        connectionsLeft -= 1;
    }

    //Remove remaining edges from 1
    for (auto v: adj[1]) {
        if (visited[v] == false)
            oneCantVisit[v] = true;
    }
}

int main() {
    cin >> N >> M >> D;
    for (int i = 1; i <= M; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);

        inDegree[u] += 1;
        inDegree[v] += 1;
    }

    if (D > inDegree[1]) {
        cout << "NO\n";
        return 0;
    }

    countNumberOfConnectedComponents();

    if (numCC > D) {
        cout << "NO\n";
        return 0;
    }

    initializeBFSStartingPosition();

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (auto v: adj[u]) {
            if (u == 1 && oneCantVisit[v])
                continue;

            if (visited[v] == false) {
                answer.push_back({u, v});

                visited[v] = true;
                Q.push(v);
            }
        }
    }

    cout << "YES\n";
    for (auto a: answer) {
        cout << a.first << " " << a.second << endl;
    }
}
