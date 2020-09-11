#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int n, m, cnt[MAXN + 3], cost[MAXN + 3];
vector<int> cheapest;

bool cmp(int a, int b) {
    return cost[a] > cost[b];
}

int main() {
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> cnt[i];

    for (int i = 1; i <= n; i++)
        cin >> cost[i];

    for (int i = 1; i <= n; i++)
        cheapest.push_back(i);

    //cheapest dish will be at back
    sort(cheapest.begin(), cheapest.end(), cmp);

    for (int i = 1; i <= m; i++) {
        int t, d;
        cin >> t >> d;

        LL totalCost = 0;
        while (d > 0) {
            if (cnt[t] > 0) {
                int take = min(cnt[t], d);
                totalCost += (LL) take * cost[t];

                d -= take;
                cnt[t] -= take;
            } else {
                while (!cheapest.empty() && cnt[cheapest.back()] == 0)
                    cheapest.pop_back();

                if (cheapest.empty())
                    break;

                int take = min(cnt[cheapest.back()], d);
                totalCost += (LL) take * cost[cheapest.back()];

                d -= take;
                cnt[cheapest.back()] -= take;
            }
        }

        if (d > 0)
            cout << 0 << endl;
        else
            cout << totalCost << endl;
    }
}
