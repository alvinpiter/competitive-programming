#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 13
#define MAXQ 100
#define DEBUG true

int N, M, Q, edgeRule[MAXN + 3][2], lcaRule[MAXQ + 3][3];
bool counted[(1 << MAXN) + 3];
LL dp[MAXN + 3][(1 << MAXN) + 3];

bool validateEdgeRule(int root, int mask, int newRoot, int newMask) {
    for (int i = 0; i < M; i++) {

        //This loop is to ease implementation only. Without this loop, we will need to check if a node belongs to mask or newMask.
        for (int k = 0; k < 2; k++) {

            //If the there are two nodes in two different mask and they both are not root and newRoot, then validation failed.
            if ((mask & (1 << edgeRule[i][0])) && (newMask & (1 << edgeRule[i][1])))  {
                if (edgeRule[i][0] != root || edgeRule[i][1] != newRoot)
                    return false;
            }

            swap(edgeRule[i][0], edgeRule[i][1]);
        }
    }

    return true;
}

bool validateLcaRule(int root, int mask, int newRoot, int newMask) {
    for (int i = 0; i < Q; i++) {
        for (int k = 0; k < 2; k++) {
            //If there are two nodes in two different mask and their lca is not root, then validation failed.
            if ((mask & (1 << lcaRule[i][0])) && (newMask & (1 << lcaRule[i][1]))) {
                if (lcaRule[i][2] != root)
                    return false;
            }

            swap(lcaRule[i][0], lcaRule[i][1]);
        }
    }

    return true;
}

int lsb(int mask) {
    return (mask & -mask);
}

LL solve(int root, int mask) {
    //There is only 1 node left
    if (mask - lsb(mask) == 0)
        return 1;

    if (dp[root][mask] != -1)
        return dp[root][mask];

    LL result = 0;
    int maskWithoutRoot = mask ^ (1 << root);

    memset(counted, false, sizeof(counted));
    for (int newMask = maskWithoutRoot; newMask > 0; newMask = (newMask - 1)&maskWithoutRoot) {
        //To avoid double counting
        if (lsb(newMask) == lsb(maskWithoutRoot)) {
            for (int newRoot = 0; newRoot < N; newRoot++) {
                if (newMask & (1 << newRoot)) {
                    if (validateEdgeRule(root, (mask^newMask), newRoot, newMask) && validateLcaRule(root, (mask^newMask), newRoot, newMask))
                        result += solve(newRoot, newMask) * solve(root, mask ^ newMask);
                }
            }
        }
    }

    return dp[root][mask] = result;
}

int main() {
    cin >> N >> M >> Q;

    for (int i = 0; i < M; i++) {
        cin >> edgeRule[i][0] >> edgeRule[i][1];

        for (int k = 0; k < 2; k++)
            edgeRule[i][k] -= 1;
    }

    for (int i = 0; i < Q; i++) {
        cin >> lcaRule[i][0] >> lcaRule[i][1] >> lcaRule[i][2];

        for (int k = 0; k < 3; k++)
            lcaRule[i][k] -= 1;

        if (lcaRule[i][0] == lcaRule[i][1] && lcaRule[i][2] != lcaRule[i][0]) {
            cout << 0 << endl;
            return 0;
        }
    }

    memset(dp, -1, sizeof(dp));
    cout << solve(0, (1 << N) - 1) << endl;
}
