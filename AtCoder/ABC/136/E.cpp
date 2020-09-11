#include<bits/stdc++.h>
using namespace std;
#define MAXN 500
#define LL long long int

int N, K, A[MAXN + 3], sumA;

bool check(int g) {
    int r[MAXN + 3];
    LL sumNeg[MAXN + 3], sumPos[MAXN + 3];

    for (int i = 1; i <= N; i++)
        r[i] = A[i]%g;

    sort(r + 1, r + N + 1);

    sumNeg[0] = 0;
    for (int i = 1; i <= N; i++) sumNeg[i] = sumNeg[i - 1] + r[i];

    sumPos[N + 1] = 0;
    for (int i = N; i >= 1; i--) sumPos[i] = sumPos[i + 1] + (g - r[i]);

    for (int i = 1; i <= N - 1; i++) {
        if (sumNeg[i] == sumPos[i + 1] && sumNeg[i] <= K)
            return true;
    }

    //Corner case, no need to perform operation
    if (sumNeg[N] == 0)
        return true;

    return false;
}

int main() {
    cin >> N >> K;

    sumA = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        sumA += A[i];
    }

    int answer = 0;
    for (int g = 1; g * g <= sumA; g++) {
        if (sumA % g == 0) {
            if (check(g)) answer = max(answer, g);
            if (check(sumA/g)) answer = max(answer, sumA/g);
        }
    }

    cout << answer << endl;
}
