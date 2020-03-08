#include<bits/stdc++.h>
using namespace std;
#define MAXN 40000
#define LL long long int

int n, m, k, a, b;
int subAWithSize[MAXN + 3], subBWithSize[MAXN + 3];

int main() {
    cin >> n >> m >> k;

    memset(subAWithSize, 0, sizeof(subAWithSize));
    memset(subBWithSize, 0, sizeof(subBWithSize));

    int cons = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        if (a == 1) {
            cons += 1;
            subAWithSize[1] += 1;
            subAWithSize[cons + 1] -= 1;
        } else {
            cons = 0;
        }
    }

    cons = 0;
    for (int i = 1; i <= m; i++) {
        cin >> b;
        if (b == 1) {
            cons += 1;
            subBWithSize[1] += 1;
            subBWithSize[cons + 1] -= 1;
        } else {
            cons = 0;
        }
    }

    for (int i = 1; i <= MAXN; i++) {
        subAWithSize[i] += subAWithSize[i - 1];
        subBWithSize[i] += subBWithSize[i - 1];
    }

    LL answer = 0;
    for (int sz = 1; sz * sz <= k; sz++) {
        if (k % sz != 0 || k/sz > MAXN)
            continue;

        answer += ((LL) subAWithSize[sz]) * subBWithSize[k/sz];

        if (sz * sz != k)
            answer += ((LL) subAWithSize[k/sz]) * subBWithSize[sz];
    }

    cout << answer << endl;
}
