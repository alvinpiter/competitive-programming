#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

int main() {
    int N, k, answer, cntOff;
    bool isOn[MAXN + 3];

    scanf("%d", &N);

    memset(isOn, true, sizeof(isOn));
    answer = cntOff = 0;

    scanf("%d", &k);
    for (int i = 1; i <= k; i++) {
        int idx;
        scanf("%d", &idx);

        for (int j = idx; j <= N; j += idx) {
            if (isOn[j])
                cntOff += 1;
            else
                cntOff -= 1;

            isOn[j] = !isOn[j];
        }

        answer = max(answer, cntOff);
    }

    printf("%d\n", answer);
}
