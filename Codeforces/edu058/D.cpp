#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int n, a[MAXN + 3], parent[MAXN + 3], dp[MAXN + 3][10], answer;
vector<int> primeFactors[MAXN + 3];
vector<int> adj[MAXN + 3];

void factorize(int idx) {
    int temp = a[idx];
    for (int d = 2; d * d <= temp; d++) {
        if (temp % d == 0) {
            primeFactors[idx].push_back(d);
            while (temp % d == 0)
                temp /= d;
        }
    }

    if (temp != 1)
        primeFactors[idx].push_back(temp);
}

//longest path from u to one of its descendant such that all the numbers are divisible by parentPrimeIdx-th prime of parent[u].
int longestPath(int u, int parentPrimeIdx) {
    if (dp[u][parentPrimeIdx] != -1)
        return dp[u][parentPrimeIdx];

    int primeIdx = -1;
    for (int i = 0; i < primeFactors[u].size(); i++) {
        if (primeFactors[u][i] == primeFactors[parent[u]][parentPrimeIdx]) {
            primeIdx = i;
            break;
        }
    }

    if (primeIdx == -1)
        return dp[u][parentPrimeIdx] = 0;
    else {
        int best = 1;
        for (auto v: adj[u]) {
            if (v != parent[u])
                best = max(best, 1 + longestPath(v, primeIdx));
        }

        return dp[u][parentPrimeIdx] = best;
    }
}

//find the parent of each node
void dfs1(int u, int prv) {
    for (auto v: adj[u]) {
        if (v != prv) {
            parent[v] = u;
            dfs1(v, u);
        }
    }
}

//traverse the tree to find the longest path
void dfs2(int u, int prv) {
    for (int i = 0; i < primeFactors[u].size(); i++) {
        vector<int> temp;
        for (auto v: adj[u]) {
            if (v != parent[u])
                temp.push_back(longestPath(v, i));
        }

        sort(temp.begin(), temp.end(), greater<int>());

        if ((int) temp.size() == 0) answer = max(answer, 1);
        if ((int) temp.size() == 1) answer = max(answer, 1 + temp[0]);
        if ((int) temp.size() > 1) answer = max(answer, 1 + temp[0] + temp[1]);
    }

    for (auto v: adj[u]) {
        if (v != prv)
            dfs2(v, u);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        factorize(i);
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //dummy
    a[0] = a[1];
    factorize(0);

    parent[1] = 0;
    dfs1(1, 0);

    memset(dp, -1, sizeof(dp));

    answer = 0;
    dfs2(1, 0);

    printf("%d\n", answer);
}
