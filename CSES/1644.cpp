#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int N, A, B;
LL prefixSum[MAXN + 3], ans;
multiset<LL> activePrefixSums;

int main() {
    cin >> N >> A >> B;

    prefixSum[0] = 0;
    for (int i = 1; i <= N; i++) {
        int number;
        cin >> number;

        prefixSum[i] = prefixSum[i - 1] + number;
    }

    ans = -1e18;
    for (int i = A; i <= B; i++)
        ans = max(ans, prefixSum[i]);

    int l = 1, r = B - A + 1;
    for (int i = l; i <= r; i++)
        activePrefixSums.insert(prefixSum[i]);

    for (int i = B + 1; i <= N; i++) {
        ans = max(ans, prefixSum[i] - *activePrefixSums.begin());

        activePrefixSums.erase(activePrefixSums.find(prefixSum[l++]));
        activePrefixSums.insert(prefixSum[++r]);
    }

    cout << ans << endl;
}
