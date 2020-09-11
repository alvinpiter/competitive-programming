#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000

int n, a[MAXN + 3], b[MAXN + 3];
vector<pair<int, int> > answer1, answer2;

int parent[MAXN + 3];

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return findSet(u) == findSet(v);
}

void joinSet(int u, int v) {
    parent[findSet(u)] = findSet(v);
}

int main() {
    cin >> n;

    for (int i = 1; i < n; i++)
        cin >> a[i] >> b[i];

    while (true) {
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        int edgeIdxToReplace = -1;
        for (int i = 1; i < n; i++) {
            if (isSameSet(a[i], b[i]))
                edgeIdxToReplace = i;
            else
                joinSet(a[i], b[i]);
        }

        if (edgeIdxToReplace == -1)
            break;

        //find two disconnected tree
        for (int i = 1; i <= n; i++) {
            if (!isSameSet(1, i)) {
                int u = findSet(1);
                int v = findSet(i);

                //replace previous edge with u-v
                answer1.push_back({a[edgeIdxToReplace], b[edgeIdxToReplace]});
                answer2.push_back({u, v});
                a[edgeIdxToReplace] = u;
                b[edgeIdxToReplace] = v;

                break;
            }
        }
    }

    cout << (int) answer1.size() << endl;
    for (int i = 0; i < (int) answer1.size(); i++) {
        cout << answer1[i].first << " " << answer1[i].second << " " << answer2[i].first << " " << answer2[i].second << endl;
    }
}
