#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define INF 1000000000

/*
A segment tree that can answer range sum query and range max query.
*/
class SegmentTree {
private:
    int N;
    pair<int, int> tree[4 * MAXN + 3]; //(sum, max)

    pair<int, int> merge(pair<int, int> node1, pair<int, int> node2) {
        return make_pair(
            node1.first + node2.first,
            max(node1.second, node2.second)
        );
    }

    void doUpdate(int node, int l, int r, int idx, int value) {
        if (idx < l || idx > r)
            return;

        if (l == r) {
            tree[node] = make_pair(value, value);
            return;
        }

        int m = (l + r)/2;
        doUpdate(2 * node, l, m, idx, value);
        doUpdate(2 * node + 1, m + 1, r, idx, value);

        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    pair<int, int> doQuery(int node, int l, int r, int le, int ri) {
        if (r < le || l > ri)
            return make_pair(0, -INF);

        if (l >= le && r <= ri)
            return tree[node];

        int m = (l + r)/2;
        pair<int, int> leftResult = doQuery(2 * node, l, m, le, ri);
        pair<int, int> rightResult = doQuery(2 * node + 1, m + 1, r, le, ri);

        return merge(leftResult, rightResult);
    }
public:
    SegmentTree(int _N) {
        N = _N;
        for (int i = 1; i <= 4 * MAXN; i++) {
            tree[i].first = 0;
            tree[i].second = -INF;
        }
    }

    void update(int idx, int value) {
        doUpdate(1, 1, N, idx, value);
    }

    int querySum(int le, int ri) {
        if (le > ri)
            return 0;
        else
            return doQuery(1, 1, N, le, ri).first;
    }

    int queryMax(int le, int ri) {
        if (le > ri)
            return -INF;
        else
            return doQuery(1, 1, N, le, ri).second;
    }
};

int N, Q;
pair<int, int> pos[MAXN + 3];

int getManhattanDistance(pair<int, int> p1, pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int getDistValue(int idx) {
    return getManhattanDistance(pos[idx], pos[idx + 1]);
}

int getBenefitValue(int idx) {
    return getManhattanDistance(pos[idx - 1], pos[idx]) + getManhattanDistance(pos[idx], pos[idx + 1]) - getManhattanDistance(pos[idx - 1], pos[idx + 1]);
}

int main() {
    ifstream fin("marathon.in");
    ofstream fout("marathon.out");

    fin >> N >> Q;
    for (int i = 1; i <= N; i++)
        fin >> pos[i].first >> pos[i].second;

    SegmentTree distTree = SegmentTree(N);
    SegmentTree benefitTree = SegmentTree(N);

    for (int i = 1; i < N; i++)
        distTree.update(i, getDistValue(i));

    for (int i = 2; i < N; i++)
        benefitTree.update(i, getBenefitValue(i));

    for (int i = 1; i <= Q; i++) {
        string op;
        int idx, x, y;

        fin >> op;
        if (op == "U") {
            fin >> idx >> x >> y;

            pos[idx] = make_pair(x, y);

            distTree.update(idx, getDistValue(idx));
            if (idx > 1)
                distTree.update(idx - 1, getDistValue(idx - 1));

            if (idx > 2)
                benefitTree.update(idx - 1, getBenefitValue(idx - 1));

            if (idx >= 2 && idx <= N - 1)
                benefitTree.update(idx, getBenefitValue(idx));

            if (idx < N - 1)
                benefitTree.update(idx + 1, getBenefitValue(idx + 1));
        } else {
            fin >> x >> y;

            int totalDistance = distTree.querySum(x, y - 1);
            int maxBenefit = max(benefitTree.queryMax(x + 1, y - 1), 0);

            fout << totalDistance - maxBenefit << endl;
        }
    }
}
