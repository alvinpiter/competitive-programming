#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define SQRTN 450
#define LL long long int

int Q, N, dfsTime, inTime[MAXN + 3], outTime[MAXN + 3], queries[MAXN + 3][3], nodeNumber[MAXN + 3];
vector<int> children[MAXN + 3], heavyNodes;
LL BIT[MAXN + 3], answerForHeavyNode[MAXN + 3];

void updateBIT(int idx, int val) {
    while (idx <= N) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

LL queryBIT(int idx) {
    LL result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

LL getSubtreeSum(int u) {
    return queryBIT(outTime[u]) - queryBIT(inTime[u] - 1);
}

void DFS(int u) {
    inTime[u] = ++dfsTime;

    for (int i = 0; i < children[u].size(); i++) {
        DFS(children[u][i]);
    }

    outTime[u] = dfsTime;
}

bool isHeavyNode(int u) {
    return children[u].size() >= SQRTN;
}

LL query(int u) {
    if (isHeavyNode(u)) {
        return answerForHeavyNode[u];
    } else {
        LL best = 0;
        for (int i = 0; i < children[u].size(); i++) {
            int v = children[u][i];
            LL subtreeSum = getSubtreeSum(v);

            best = max(best, subtreeSum);
        }

        return best;
    }
}

void update(int u, int val) {
    updateBIT(inTime[u], val);

    for (int i = 0; i < heavyNodes.size(); i++) {
        int parent = heavyNodes[i];

        if (inTime[u] >= inTime[parent] && inTime[u] <= outTime[parent]) {
            int lo = 0, hi = children[parent].size() - 1, mid;
            while (hi >= lo) {
                mid = (lo + hi)/2;
                int child = children[parent][mid];

                if (outTime[child] < inTime[u])
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }

            int child = children[parent][lo];
            LL subtreeSum = getSubtreeSum(child);
            answerForHeavyNode[parent] = max(answerForHeavyNode[parent], subtreeSum);
        }
    }
}

int main() {
    cin >> Q;

    N = 1;
    for (int i = 1; i <= Q; i++) {
        cin >> queries[i][0];

        if (queries[i][0] == 1) {
            cin >> queries[i][1] >> queries[i][2];
            children[queries[i][1]].push_back(++N);
            nodeNumber[i] = N;
        } else {
            cin >> queries[i][1];
        }
    }

    dfsTime = 0;
    DFS(1);

    for (int i = 1; i <= N; i++) {
        if (isHeavyNode(i))
            heavyNodes.push_back(i);
    }

    memset(BIT, 0, sizeof(BIT));
    memset(answerForHeavyNode, 0, sizeof(answerForHeavyNode));

    for (int i = 1; i <= Q; i++) {
        if (queries[i][0] == 1) {
            update(nodeNumber[i], queries[i][2]);
        } else {
            cout << query(queries[i][1]) << endl;
        }
    }
}
