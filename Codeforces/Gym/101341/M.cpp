#include<bits/stdc++.h>
using namespace std;

int main() {
    int n;
    vector<pair<int, int> > kills, logs;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        kills.push_back({a, i});
    }

    bool possible = true;

    sort(kills.begin(), kills.end()); //sort player based on number of kills (smaller first)
    int ptr = 0; //points to player that is still alive

    for (int i = 0; i < n; i++) {
        if (kills[i].first == 0)
            continue;

        for (int rep = 0; rep < kills[i].first; rep++) {
            if (ptr < i) {
                logs.push_back({kills[i].second, kills[ptr].second});
                ptr += 1;
            } else {
                possible = false;
                break;
            }
        }

        if (possible == false)
            break;
    }

    if (possible) {
        printf("YES\n");
        for (auto log: logs)
            printf("%d %d\n", log.first, log.second);
    } else {
        printf("NO\n");
    }
}
