#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int n, u[MAXN + 3], v[MAXN + 3], degree[MAXN + 3], answer[MAXN + 3];
vector<pair<int, int> > degrees;

int main() {
    scanf("%d", &n);

    memset(degree, 0, sizeof(degree));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d%d", &u[i], &v[i]);

        degree[u[i]] += 1;
        degree[v[i]] += 1;
    }

    for (int i = 0; i < n - 1; i++) {
        int d = min(degree[u[i]], degree[v[i]]);
        degrees.push_back({d, i});
    }

    sort(degrees.begin(), degrees.end());

    for (int i = 0; i < n - 1; i++)
        answer[degrees[i].second] = i;

    for (int i = 0; i < n - 1; i++)
        printf("%d\n", answer[i]);
}
