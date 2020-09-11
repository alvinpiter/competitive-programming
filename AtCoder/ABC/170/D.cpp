#include<bits/stdc++.h>
using namespace std;
#define MAXA 1000000

int main() {
    int N, cnt[MAXA + 3];
    bool divisorExist[MAXA + 3];

    cin >> N;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= N; i++) {
        int A;
        cin >> A;

        cnt[A] += 1;
    }

    memset(divisorExist, false, sizeof(divisorExist));
    for (int i = 1; i <= MAXA; i++) {
        if (cnt[i] > 0) {
            for (int j = 2 * i; j <= MAXA; j += i) {
                divisorExist[j] = true;
            }
        }
    }

    int answer = 0;
    for (int i = 1; i <= MAXA; i++) {
        if (cnt[i] == 1 && !divisorExist[i])
            answer += 1;
    }

    cout << answer << endl;
}
