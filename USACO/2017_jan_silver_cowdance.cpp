#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000

int N, T, d[MAXN + 3];

int main() {
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    cin >> N >> T;
    for (int i = 1; i <= N; i++)
        cin >> d[i];

    int lo = 1, hi = N, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        multiset<int> finishTime;
        for (int i = 1; i <= mid; i++)
            finishTime.insert(d[i]);

        int lastId = mid;
        int maxFinishTime = 0;

        while (!finishTime.empty()) {
            auto ptr = finishTime.begin();
            int t = *ptr;

            finishTime.erase(ptr);

            maxFinishTime = max(maxFinishTime, t);
            if (lastId != N) {
                lastId += 1;
                finishTime.insert(t + d[lastId]);
            }
        }

        if (maxFinishTime <= T)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << lo << endl;
}
