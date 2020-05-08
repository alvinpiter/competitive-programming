#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

/*
There are two cases:
* Find subtree u with size 2/3 and subtree v with size 1/3 where v is descendant of u
* Find subtree u with size 1/3 and subtree v with size 1/3 where u is not descendant of each other

Be careful not to output the root.
*/

//third[u] = node with size 1/3 below subtree u

int n, root, sumTemp, sum[MAXN + 3], third[MAXN + 3], temp[MAXN + 3];
int ans1, ans2;
vector<int> children[MAXN + 3];

void DFS(int u) {
    sum[u] = temp[u];

    int thirdIdx = -1;
    for (auto v: children[u]) {
        DFS(v);
        sum[u] += sum[v];
        if (third[v] != -1) thirdIdx = third[v];
    }

    third[u] = -1;
    if (thirdIdx != -1)
        third[u] = thirdIdx;
    else if (3 * sum[u] == sumTemp)
        third[u] = u;

    if (u != root && 3 * sum[u] == 2 * sumTemp && thirdIdx != -1) {
        ans1 = u;
        ans2 = thirdIdx;
    }
}

int main() {
    scanf("%d", &n);

    sumTemp = 0;
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d%d", &p, &temp[i]);

        sumTemp += temp[i];

        if (p != 0)
            children[p].push_back(i);
        else
            root = i;
    }

    if (sumTemp % 3 != 0) {
        printf("-1\n");
        return 0;
    }

    ans1 = ans2 = -1;
    DFS(root);

    if (ans1 != -1) {
        printf("%d %d\n", ans1, ans2);
    } else {
        vector<int> candidate;
        for (int i = 1; i <= n; i++) {
            if (third[i] != -1 && third[i] == i)
                candidate.push_back(i);
        }

        if (candidate.size() > 1) {
            printf("%d %d\n", candidate[0], candidate[1]);
        } else {
            printf("-1\n");
        }
    }
}
