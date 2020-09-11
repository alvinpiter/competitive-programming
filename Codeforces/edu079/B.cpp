#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int main() {
    int T, N;
    LL S, prefixSum[MAXN + 3];

    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        scanf("%d%lld", &N, &S);

        prefixSum[0] = 0;
        for (int i = 1; i <= N; i++) {
            int a;
            scanf("%d", &a);

            prefixSum[i] = prefixSum[i - 1] + a;
        }

        int maxi = 0;
        int answer;
        for (int i = 0; i <= N; i++) {
            LL prevSum = (i == 0 ? 0 : prefixSum[i - 1]);

            if (prevSum > S)
                break;

            int lo = i + 1, hi = N, mid;
            while (hi >= lo) {
                mid = (lo + hi)/2;

                LL sum = prevSum + prefixSum[mid] - prefixSum[i];
                if (sum <= S)
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }

            int count = (i == 0 ? hi : hi - 1);
            if (count > maxi) {
                maxi = count;
                answer = i;
            }
        }

        cout << answer << endl;
    }
}
