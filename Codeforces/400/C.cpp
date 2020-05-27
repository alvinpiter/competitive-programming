#include<bits/stdc++.h>
using namespace std;
#define INF 1e15
#define LL long long int

int n, k, a[100005], answer;
set<LL> pk; //a set that contains all non-negative integer power of k
map<LL, int> cntPrefix; //cntPrefix[s] = how many prefix with prefix sum s

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    if (abs(k) == 1) {
        pk.insert(1);
        if (k == -1)
            pk.insert(-1);
    } else {
        LL powerK = 1;
        pk.insert(powerK);

        while (abs(powerK) <= INF) {
            powerK *= k;
            pk.insert(powerK);
        }
    }

    LL answer = 0;
    LL prefixSum = 0;
    cntPrefix[prefixSum] = 1;

    for (int i = 1; i <= n; i++) {
        prefixSum += a[i];
        for (auto powerK: pk)
            answer += cntPrefix[prefixSum - powerK];

        cntPrefix[prefixSum] += 1;
    }

    cout << answer << endl;
}
