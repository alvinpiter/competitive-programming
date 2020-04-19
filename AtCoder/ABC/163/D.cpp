#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007

int main() {
    LL N, K, prefix[200003];

    cin >> N >> K;

    prefix[0] = 0;
    for (int i = 1; i <= N; i++)
        prefix[i] = prefix[i - 1] + i;

    LL answer = 0;
    for (int k = K; k <= N + 1; k++) {
        LL mini = prefix[k - 1];
        LL maxi = prefix[N] - (N - k < 0 ? 0 : prefix[N - k]);

        LL temp = (maxi - mini + 1)%MOD;

        answer = (answer + temp)%MOD;
    }

    cout << answer << endl;
}
