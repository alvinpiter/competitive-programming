#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define MAXM 50000

int N, M, indegree[MAXN + 3];
int order[MAXN + 3];
vector<int> rule[MAXM + 3];
vector<int> adj[MAXN + 3];

//Check if there is a topological order if we follow the first x rule.
//If there is, put the result in order array.
bool checkUptoRule(int x) {
    //Build the graph
    for (int i = 1; i <= N; i++) {
        adj[i].clear();
        indegree[i] = 0;
    }

    for (int i = 1; i <= x; i++) {
        for (int j = 1; j < rule[i].size(); j++) {
            int u = rule[i][j - 1], v = rule[i][j];
            adj[u].push_back(v);
            indegree[v]++;
        }
    }

    priority_queue<int> pq;
    for (int i = 1; i <= N; i++) {
        if (indegree[i] == 0)
            pq.push(-i);
    }

    for (int i = 1; i <= N; i++) {
        if (pq.empty())
            return false;

        int u = -pq.top(); pq.pop();
        for (auto v: adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                pq.push(-v);
        }

        order[i] = u;
    }

    return true;
}

int main() {
    freopen("milkorder.in", "r", stdin);
    freopen("milkorder.out", "w", stdout);

    scanf("%d%d", &N, &M);
    for (int i = 1; i <= M; i++) {
        int m, r;
        scanf("%d", &m);

        for (int j = 1; j <= m; j++) {
            scanf("%d", &r);

            rule[i].push_back(r);
        }
    }

    //Find the last rule that can be fulfilled without having a cycle
    int lo = 1, hi = M, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (checkUptoRule(mid) == true) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    //We can fulfill upto rule hi.
    checkUptoRule(hi);

    for (int i = 1; i <= N; i++) {
        if (i > 1)
            printf(" ");

        printf("%d", order[i]);
    }
    printf("\n");
}
