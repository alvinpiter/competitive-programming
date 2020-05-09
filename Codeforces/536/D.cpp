#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n, m;
bool inQueue[MAXN + 3];
vector<int> adj[MAXN + 3];
vector<int> answer;

int main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    priority_queue<int> pq;
    inQueue[1] = true;
    pq.push(-1);

    while (!pq.empty()) {
        int u = -pq.top(); pq.pop();

        answer.push_back(u);

        for (auto v: adj[u]) {
            if (!inQueue[v]) {
                inQueue[v] = true;
                pq.push(-v);
            }
        }
    }

    for (auto a: answer)
        cout << a << " ";
    cout << endl;
}
