#include<bits/stdc++.h>
using namespace std;
#define MAXN 1023

/*
here height is defined as the length of path from root to leaf.
*/

int n, h, dist[MAXN + 3][MAXN + 3], parent[MAXN + 3];
bool isLeaf[MAXN + 3];

int ask(int u, int v) {
    if (dist[u][v] != -1)
        return dist[u][v];

    cout << "? " << u << " " << v << endl;
    cout.flush();

    int d;
    cin >> d;

    dist[u][v] = dist[v][u] = d;

    return dist[u][v];
}

void answer() {
    cout << "!";
    for (int i = 1; i <= n; i++)
        cout << " " << parent[i];

    cout << endl;
    cout.flush();
}

void findLeaves() {
    int leaf1 = 1;
    for (int i = 2; i <= n; i++) {
        if (ask(1, i) > ask(1, leaf1))
            leaf1 = i;
    }

    int leaf2;
    for (int i = 1; i <= n; i++) {
        if (ask(leaf1, i) == 2 * h) {
            isLeaf[i] = true;
            leaf2 = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (ask(leaf2, i) == 2 * h) {
            isLeaf[i] = true;
        }
    }
}

void findTree(vector<int>& nodes, int height, int par) {
    if (height == 0) {
        parent[nodes[0]] = par;
        return;
    }

    int leaf1;
    for (auto node: nodes) {
        if (isLeaf[node])
            leaf1 = node;
    }

    int leaf2;
    for (auto node: nodes) {
        if (isLeaf[node] && ask(leaf1, node) == 2 * height) {
            leaf2 = node;
            break;
        }
    }

    int root;
    vector<int> group1, group2;
    for (auto node: nodes) {
        int d1 = ask(leaf1, node);
        int d2 = ask(leaf2, node);

        if (d1 < d2) {
            group1.push_back(node);
        } else if (d2 < d1) {
            group2.push_back(node);
        } else if (d1 == d2) {
            root = node;
        }
    }

    parent[root] = par;
    findTree(group1, height - 1, root);
    findTree(group2, height - 1, root);
}

int main() {
    cin >> n;

    //Initialize distance cache
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            dist[i][j] = (i == j ? 0 : -1);
    }

    //Calculate height of the tree
    while ((1 << h) < n + 1)
        h += 1;

    h -= 1;

    memset(isLeaf, false, sizeof(isLeaf));
    findLeaves();

    vector<int> nodes;
    for (int i = 1; i <= n; i++)
        nodes.push_back(i);

    findTree(nodes, h, 0);
    answer();
}
