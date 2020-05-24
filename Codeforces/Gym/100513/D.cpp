#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    int n, nLow, nHigh;
    LL m;
    vector<pair<LL, int> > lows, highs;

    scanf("%d%lld", &n, &m);
    for (int i = 0; i < n; i++) {
        LL a;
        int l;
        scanf("%lld%d", &a, &l);

        if (l == 0)
            highs.push_back({a, i});
        else
            lows.push_back({a, i});
    }

    nLow = (int) lows.size();
    nHigh = (int) highs.size();

    sort(highs.begin(), highs.end());
    reverse(highs.begin(), highs.end());

    sort(lows.begin(), lows.end());
    reverse(lows.begin(), lows.end());

    vector<LL> sumHighs;
    if (!highs.empty()) {
        sumHighs.push_back(highs[0].first);
        for (int i = 1; i < nHigh; i++)
            sumHighs.push_back(highs[i].first + sumHighs.back());
    }

    vector<LL> sumLows;
    if (!lows.empty()) {
        sumLows.push_back(lows[0].first);
        for (int i = 1; i < nLow; i++)
            sumLows.push_back(lows[i].first + sumLows.back());
    }

    int miniNumServer = n;
    int miniNumLowServer;

    for (int cntLow = 0; cntLow <= nLow; cntLow++) {
        LL sumLow = (cntLow == 0 ? 0 : sumLows[cntLow - 1]);
        LL need = m - sumLow;

        //Find out how many high voltage servers needed
        int l = 0, r = nHigh, m;
        while (r >= l) {
            m = (l + r)/2;

            LL sumHigh = (m == 0 ? 0 : sumHighs[m - 1]);

            if (sumHigh >= need)
                r = m - 1;
            else
                l = m + 1;
        }

        if (l > nHigh)
            continue;

        int numServer = cntLow + l;

        if (numServer <= miniNumServer) {
            miniNumServer = numServer;
            miniNumLowServer = cntLow;
        }
    }

    vector<int> indices;
    for (int i = 0; i < miniNumLowServer; i++)
        indices.push_back(lows[i].second);

    for (int i = 0; i < miniNumServer - miniNumLowServer; i++)
        indices.push_back(highs[i].second);

    cout << miniNumServer << " " << miniNumLowServer << endl;
    for (auto i: indices)
        printf("%d ", i + 1);
    printf("\n");
}
