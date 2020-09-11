#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, K, a[MAXN + 3];
LL prefixSum[MAXN + 3], answer;
map<int, int> cnt;

//Get count and sum of numbers that is higher than num
pair<int, LL> getHigher(int num) {
    int idx = lower_bound(a + 1, a + N + 1, num + 1) - a;
    return {N - idx + 1, prefixSum[N] - prefixSum[idx - 1]};
}

//Get count and sum of numbers that is lower than num
pair<int, LL> getLower(int num) {
    int idx = (lower_bound(a + 1, a + N + 1, num) - a) - 1;
    return {idx, prefixSum[idx]};
}

int main() {
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &a[i]);

        if (cnt.find(a[i]) != cnt.end())
            cnt[a[i]] += 1;
        else
            cnt[a[i]] = 1;
    }

    sort(a + 1, a + N + 1);

    prefixSum[0] = 0;
    for (int i = 1; i <= N; i++)
        prefixSum[i] = prefixSum[i - 1] + a[i];

    answer = 1e18;

    //For each i, we try to make a[i] exist at least k times
    for (int i = 1; i <= N; i++) {
        if (cnt[a[i]] >= K) {
            answer = 0;
            break;
        }

        int need = K - cnt[a[i]];

        auto lowerStats = getLower(a[i]);
        auto higherStats = getHigher(a[i]);

        int lowerCount = lowerStats.first;
        LL lowerSum = lowerStats.second;
        LL lowerCost = ((LL) a[i] - 1) * lowerCount - lowerSum;

        int higherCount = higherStats.first;
        LL higherSum = higherStats.second;
        LL higherCost = higherSum - ((LL) a[i] + 1) * higherCount;

        LL cost = 0;
        int take;

        LL costLowerFirst = 0;
        LL costHigherFirst = 0;

        //Calculate cost if we equalize lower first
        take = min(need, lowerCount);
        costLowerFirst += lowerCost + take;

        if (need - take > 0)
            costLowerFirst += higherCost + (need - take);

        //Calculate cost if we equalize higher first
        take = min(need, higherCount);
        costHigherFirst += higherCost + take;

        if (need - take > 0)
            costHigherFirst += lowerCost + (need - take);

        answer = min(answer, min(costLowerFirst, costHigherFirst));
    }

    printf("%lld\n", answer);
}
