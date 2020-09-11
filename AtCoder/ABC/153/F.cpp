#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

//prefixSum[i] -> how many bombs affect i-th monster

int N, D, A;
LL prefixSum[MAXN + 3], answer;
pair<int, int> monsters[MAXN + 3];

int main() {
    scanf("%d%d%d", &N, &D, &A);
    for (int i = 1; i <= N; i++) {
        int X, H;
        scanf("%d%d", &X, &H);

        monsters[i] = {X, H};
    }

    sort(monsters + 1, monsters + N + 1);

    memset(prefixSum, 0, sizeof(prefixSum));
    answer = 0;

    for (int i = 1; i <= N; i++) {
        prefixSum[i] += prefixSum[i - 1];
        LL H = (LL) monsters[i].second - prefixSum[i] * A;

        if (H <= 0)
            continue;
        else {
            int cntBomb = H/A + (H%A == 0 ? 0 : 1);

            //find first monster that is not affected by this bomb
            int lo = i, hi = N, mid;
            while (hi >= lo) {
                mid = (lo + hi)/2;
                if (monsters[mid].first - monsters[i].first <= 2 * D)
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }

            prefixSum[i] += cntBomb;
            prefixSum[lo] -= cntBomb;

            answer += cntBomb;
        }
    }

    printf("%lld\n", answer);
}
