#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXK 200000

int main() {
    int N, K, cnt[MAXK + 3];

    cin >> N >> K;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; i++)
        cnt[i%K] += 1;

    LL answer = 0;
    for (int i = 0; i < K; i++) {
        if ((2 * i)%K == 0) {
            LL temp = (LL) cnt[i] * cnt[i] * cnt[i];
            answer += temp;
        }
    }

    cout << answer << endl;
}
