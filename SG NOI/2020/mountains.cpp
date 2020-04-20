#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 300000

int N, M;
LL H[MAXN + 3], answer;
int prefix[MAXN + 3], suffix[MAXN + 3]; //BIT
vector<LL> uniqH;

void update(int bit[], int idx, int val) {
    while (idx <= M) {
        bit[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int bit[], int idx) {
    int result = 0;
    while (idx > 0) {
        result += bit[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int id(LL h) {
    return (lower_bound(uniqH.begin(), uniqH.end(), h) - uniqH.begin()) + 1;
}

int main() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%lld", &H[i]);
        uniqH.push_back(H[i]);
    }

    sort(uniqH.begin(), uniqH.end());
    uniqH.resize(distance(uniqH.begin(), unique(uniqH.begin(), uniqH.end())));

    M = (int) uniqH.size();

    memset(prefix, 0, sizeof(prefix));
    memset(suffix, 0, sizeof(suffix));

    for (int i = 2; i <= N; i++)
        update(suffix, id(H[i]), 1);

    answer = 0;
    for (int i = 2; i < N; i++) {
        update(prefix, id(H[i - 1]), 1);
        update(suffix, id(H[i]), -1);

        int numLeft = query(prefix, id(H[i]) - 1);
        int numRight = query(suffix, id(H[i]) - 1);
        answer += (LL) numLeft * numRight;
    }

    printf("%lld\n", answer);
}
