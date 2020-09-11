#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int n;
LL sum;
vector<int> nums;
LL BIT[MAXN + 3]; //to store the updates

void update(int idx, int val) {
    while (idx <= n) {
        BIT[idx] += val;
        idx += (idx & -idx);
    }
}

LL query(int idx) {
    LL result = 0;
    while (idx > 0) {
        result += BIT[idx];
        idx -= (idx & -idx);
    }

    return result;
}

LL rsq(int l, int r) {
    return query(r) - query(l - 1);
}

int main() {
    nums.push_back(0); //dummy, to make the vector's indices 1-based
    nums.push_back(0);

    scanf("%d", &n);

    sum = 0;
    for (int i = 1; i <= n; i++) {
        int t;

        scanf("%d", &t);
        if (t == 1) {
            int a, x;
            scanf("%d%d", &a, &x);
            update(a, x);

            sum += a * x;
        } else if (t == 2) {
            int k;
            scanf("%d", &k);

            sum += k;

            int idx = (int) nums.size();
            nums.push_back(-k + rsq(idx, n));
        } else {
            int idx = (int) nums.size() - 1;
            int num = rsq(idx, n) - nums.back();

            sum -= num;
            nums.pop_back();
        }

        int sz = (int) nums.size() - 1;
        printf("%.7lf\n", (1.0 * sum)/sz);
    }
}
