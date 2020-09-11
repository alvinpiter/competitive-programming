#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
Model the problem as graph. If 2 particle can interact, add an edge between them.
The smallest number of particle that may remain equals to the number of connected component in the graph.
This is because for each connected component, there is a sequence of interactions such that
only 1 particle left.

Building the graph naively takes O(n^2). We can optimize it by take a look at points
that form a "stair", that is the point with minimal y in each x coordinate. Also note that
the y coordinate of two adjacent stair must be strictly decreasing.

After that, we decide if two adjacent point in the stair is connected. We can do this by checking if
there is another point that interact with both these points. We can do this with line sweep.

Finally, we run DFS in each point in stair.
*/

struct Point {
    int x, y, index;
    Point(int _x, int _y, int _index): x(_x), y(_y), index(_index) {}
    bool operator<(Point other) const {
        if (x == other.x)
            return y < other.y;
        else
            return x < other.x;
    }
};

int N, M;
bool visited[MAXN + 3];
vector<Point> points;
vector<Point> stair;
vector<int> adj[MAXN + 3];

void DFS(int u) {
    visited[u] = true;
    for (auto v: adj[u]) {
        if (!visited[v])
            DFS(v);
    }
}

int main() {
    freopen("moop.in", "r", stdin);
    freopen("moop.out", "w", stdout);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int x, y;
        cin >> x >> y;

        points.push_back(Point(x, y, i));
    }

    sort(points.begin(), points.end());

    //Build the stair
    for (int i = 0; i < N; ) {
        //make sure the y coordinate is strictly decreasing
        if (stair.empty() || stair.back().y > points[i].y)
            stair.push_back(points[i]);

        int j = i;
        while (j < N && points[j].x == points[i].x)
            j++;

        i = j;
    }

    //Try to connect adjacent stair, starting from the right most one
    set<int> activeY;
    int ptr = N - 1;
    for (int i = stair.size() - 2; i >= 0; i--) {
        while (ptr >= 0 && points[ptr].x >= stair[i + 1].x) {
            activeY.insert(points[ptr].y);
            ptr -= 1;
        }

        auto ptr = activeY.lower_bound(stair[i].y);
        if (ptr != activeY.end()) {
            //there is a point that connect this two stair
            int u = stair[i].index, v = stair[i + 1].index;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    memset(visited, false, sizeof(visited));

    int numCC = 0;
    for (int i = 0; i < stair.size(); i++) {
        int u = stair[i].index;
        if (!visited[u]) {
            numCC += 1;
            DFS(u);
        }
    }

    cout << numCC << endl;
}
