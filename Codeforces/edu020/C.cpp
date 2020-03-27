#include<bits/stdc++.h>
using namespace std;
#define LL long long int

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    LL n, k, mini, maxGCD = -1;

    cin >> n >> k;

    //To avoid overflow
    if (k >= 200000) {
        cout << -1 << endl;
        return 0;
    }

    mini = (k * k + k)/2;
    for (LL div = 1; div * div <= n; div++) {
        if (n % div == 0) {
            if (n/div >= mini) maxGCD = max(maxGCD, div);
            if (div >= mini) maxGCD = max(maxGCD, n/div);
        }
    }

    if (maxGCD == -1)
        cout << -1 << endl;
    else {
        for (int i = 1; i < k; i++)
            cout << maxGCD * i << " ";

        cout << (k + (n/maxGCD - mini)) * maxGCD << endl;
    }
}
