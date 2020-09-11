#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int T, N, B, A[MAXN + 3];

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> B;
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);

        sort(A, A + N);

        int answer = 0;
        for (int i = 0; i < N; i++) {
            if (B >= A[i]) {
                answer += 1;
                B -= A[i];
            }
        }

        printf("Case #%d: %d\n", cases, answer);
    }
}
