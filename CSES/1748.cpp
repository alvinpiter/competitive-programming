#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define MAXN 200000

int N, X[MAXN + 3];
vector<int> uniqX;
int BIT[MAXN + 3];

//query(x) -> how many increasing subsequence whose last element is at most x.

void update(int idx, int val) {
    while (idx <= N) {
        BIT[idx] = (BIT[idx] + val)%MOD;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result = (result + BIT[idx])%MOD;
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &X[i]);
        uniqX.push_back(X[i]);
    }

    //normalize X
    sort(uniqX.begin(), uniqX.end());
    uniqX.resize(distance(uniqX.begin(), unique(uniqX.begin(), uniqX.end())));

    for (int i = 1; i <= N; i++)
        X[i] = (lower_bound(uniqX.begin(), uniqX.end(), X[i]) - uniqX.begin()) + 1;

    memset(BIT, 0, sizeof(0));

    int answer = 0;
    for (int i = 1; i <= N; i++) {
        int curr = 1;

        curr = (curr + query(X[i] - 1))%MOD;
        answer = (answer + curr)%MOD;

        update(X[i], curr);
    }

    printf("%d\n", answer);
}
