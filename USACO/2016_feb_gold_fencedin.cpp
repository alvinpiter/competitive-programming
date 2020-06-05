#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 2000

/*
Treat each region as a vertex in a graph. The length of fence between two neighboring
regions will be the cost to connect these regions. This is MST problem.

Notice that there are roughly 4*n*m edges in the graph, but many of these edges has the same length.
For example all the edges between two neighboring cells
in the same column have the same length. With this observation, we can reduce the number of important
edges downto just n + m (some verticals, some horizontals). Let's define horizontalEdge as edge that connect two cells at the same row.
Let's say we are currently processing a horizontal edge at some row, then we will have to merge all
cells at this row. Do the same with verticalEdge.

When processing horizontal and vertical edges, we can use technique similar with merge operation in merge sort.
*/

int parent[(MAXN + 1)*(MAXN + 1) + 3];

int findSet(int u) {
    return (u == parent[u] ? u : parent[u] = findSet(parent[u]));
}

bool isSameSet(int u, int v) {
    return (findSet(u) == findSet(v));
}

void joinSet(int u, int v) {
    parent[findSet(u)] = findSet(v);
}

int A, B, n, m, a[MAXN + 3], b[MAXN + 3];
vector<pair<int, int> > verticalEdges; //{length, column}
vector<pair<int, int> > horizontalEdges; //{length, row}
LL mst;

//convert row and column position into single integer
int id(int r, int c) {
    return (r - 1)*(n + 1) + c;
}

void merge(int r1, int c1, int r2, int c2, int cost) {
    int u = id(r1, c1), v = id(r2, c2);
    if (!isSameSet(u, v)) {
        mst += cost;
        joinSet(u, v);
    }
}

void mergeRow(int row, int cost) {
    for (int j = 1; j <= n; j++)
        merge(row, j, row, j + 1, cost);
}

void mergeColumn(int col, int cost) {
    for (int i = 1; i <= m; i++)
        merge(i, col, i + 1, col, cost);
}

int main() {
    freopen("fencedin.in", "r", stdin);
    freopen("fencedin.out", "w", stdout);

    scanf("%d%d%d%d", &A, &B, &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= m; i++)
        scanf("%d", &b[i]);

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);

    a[0] = 0;
    a[n + 1] = A;

    b[0] = 0;
    b[m + 1] = B;

    for (int j = 1; j <= n + 1; j++)
        verticalEdges.push_back({a[j] - a[j - 1], j});

    for (int i = 1; i <= m + 1; i++)
        horizontalEdges.push_back({b[i] - b[i - 1], i});

    //Modified Kruskal's algorithm
    sort(verticalEdges.begin(), verticalEdges.end(), greater<pair<int, int> >());
    sort(horizontalEdges.begin(), horizontalEdges.end(), greater<pair<int, int> >());

    for (int i = 1; i <= (n + 1)*(m + 1); i++)
        parent[i] = i;

    mst = 0;
    while (!verticalEdges.empty() && !horizontalEdges.empty()) {
        if (verticalEdges.back().first < horizontalEdges.back().first) {
            mergeColumn(verticalEdges.back().second, verticalEdges.back().first);
            verticalEdges.pop_back();
        } else {
            mergeRow(horizontalEdges.back().second, horizontalEdges.back().first);
            horizontalEdges.pop_back();
        }
    }

    while (!verticalEdges.empty()) {
        mergeColumn(verticalEdges.back().second, verticalEdges.back().first);
        verticalEdges.pop_back();
    }

    while (!horizontalEdges.empty()) {
        mergeRow(horizontalEdges.back().second, horizontalEdges.back().first);
        horizontalEdges.pop_back();
    }

    printf("%lld\n", mst);
}
