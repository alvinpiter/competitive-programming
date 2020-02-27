#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, A, B, K, H, answer;
int numTechNeeded[MAXN + 3];

int main() {
    scanf("%d%d%d%d", &N, &A, &B, &K);
    for (int i = 0; i < N; i++) {
        scanf("%d", &H);

        int rem = H%(A + B);
        if (rem == 0)
            rem = A + B;

        numTechNeeded[i] = (rem/A + (rem%A == 0 ? 0 : 1)) - 1;
    }

    sort(numTechNeeded, numTechNeeded + N);

    answer = 0;
    for (int i = 0; i < N; i++) {
        if (K >= numTechNeeded[i]) {
            K -= numTechNeeded[i];
            answer += 1;
        }
    }

    printf("%d\n", answer);
}
