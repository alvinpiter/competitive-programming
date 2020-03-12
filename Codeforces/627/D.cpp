#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int n, a[MAXN + 3], b[MAXN + 3];
vector<int> uniqs;
int BIT[2 * MAXN + 3];

void update(int idx, int val) {
    while (idx <= 2 * n) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = 0; i < n; i++) {
        uniqs.push_back(a[i] - b[i]);
        uniqs.push_back(-(a[i] - b[i]));
    }

    sort(uniqs.begin(), uniqs.end());
    uniqs.resize(distance(uniqs.begin(), unique(uniqs.begin(), uniqs.end())));

    LL result = 0;
    for (int i = 0; i < n; i++) {
        int now = a[i] - b[i];
        int idxNow = lower_bound(uniqs.begin(), uniqs.end(), now) - uniqs.begin() + 1;

        result += query(idxNow - 1);

        int toInsert = -(a[i] - b[i]);
        int idxToInsert = lower_bound(uniqs.begin(), uniqs.end(), toInsert) - uniqs.begin() + 1;

        update(idxToInsert, 1);
    }

    cout << result << endl;
}
