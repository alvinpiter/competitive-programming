#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define INF 1e18
#define MAXN 300000

/*
Let's fix some F. And then we calculate the remaining fuel at each station, Frem(i). The formula:
Frem(i) = F - Xi + (sum of A of station j, where Xj < Xi)

We can reach the goal, if Frem(i) >= 0 for all i.

We will process the fuel stations in decreasing order of its B. Whenever we process a new
fuel station, we will update Frem(i) for all stations that is to the right of new station
by new fuel station's A. To do fast update/query, we should maintain a segment tree that can support:
* range addition update
* range min query
*/

struct FuelStation {
    int X, A, B;
    FuelStation(int _X, int _A, int _B): X(_X), A(_A), B(_B) {}
    bool operator<(FuelStation other) const {
        return B < other.B;
    }
};

int N, D, numUniqX;
LL tree[4 * MAXN + 3], lazy[4 * MAXN + 3];
vector<int> uniqX;
vector<FuelStation> stations;

LL evaluate(int node) {
    return tree[node] + lazy[node];
}

void pushDown(int node) {
    lazy[2 * node] += lazy[node];
    lazy[2 * node + 1] += lazy[node];
    lazy[node] = 0;
}

void pullUp(int node) {
    tree[node] = min(evaluate(2 * node), evaluate(2 * node + 1));
}

//Add on range
void update(int node, int l, int r, int le, int ri, int val) {
    if (r < le || l > ri)
        return;

    if (l >= le && r <= ri) {
        lazy[node] += val;
        return;
    }

    pushDown(node);

    int m = (l + r)/2;
    update(2 * node, l, m, le, ri, val);
    update(2 * node + 1, m + 1, r, le, ri, val);

    pullUp(node);
}

void update(int le, int ri, int val) {
    update(1, 1, numUniqX, le, ri, val);
}

LL query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return INF;

    if (l >= le && r <= ri)
        return evaluate(node);

    pushDown(node);

    int m = (l + r)/2;
    LL leftResult = query(2 * node, l, m, le, ri);
    LL rightResult = query(2 * node + 1, m + 1, r, le, ri);

    pullUp(node);

    return min(leftResult, rightResult);
}

LL query(int le, int ri) {
    return query(1, 1, numUniqX, le, ri);
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = -uniqX[l - 1];
        return;
    }

    int m = (l + r)/2;
    build(2 * node, l, m);
    build(2 * node + 1, m + 1, r);

    tree[node] = min(tree[2 * node], tree[2 * node + 1]);
}

int main() {
    scanf("%d%d", &N, &D);
    for (int i = 1; i <= N; i++) {
        int x, a, b;
        scanf("%d%d%d", &x, &a, &b);

        stations.push_back(FuelStation(x, a, b));
        uniqX.push_back(x);
    }

    //Include starting and ending position
    stations.push_back(FuelStation(0, 0, 1e9 + 1));
    stations.push_back(FuelStation(D, 0, 1e9 + 1));
    uniqX.push_back(0);
    uniqX.push_back(D);

    //normalize x
    sort(uniqX.begin(), uniqX.end());
    uniqX.resize(distance(uniqX.begin(), unique(uniqX.begin(), uniqX.end())));
    numUniqX = (int) uniqX.size();

    build(1, 1, numUniqX);

    int minF = 1e9 + 1;

    //Process the station starting from the largest B
    sort(stations.begin(), stations.end());
    for (int i = stations.size() - 1; i >= 0; i--) {
        int F = stations[i].B;

        /*
        Include stations[i].A into the data structure.
        We should update the remaining fuel at station j, where stations[j].X > stations[i].X
        */
        int normalizedX = (lower_bound(uniqX.begin(), uniqX.end(), stations[i].X) - uniqX.begin()) + 1;
        update(normalizedX + 1, numUniqX, stations[i].A);

        /*
        Get the minimal remaining fuel at active stations.
        If the minimal is < 0, then we can't go to destination.
        */
        int mini = F + query(1, numUniqX);
        if (mini < 0)
            continue;
        else
            minF = min(minF, F - mini);
    }

    printf("%d\n", minF);
}

/*
5 100
50 30 25
50 40 25
25 25 25
75 20 25
5 5 25
*/
