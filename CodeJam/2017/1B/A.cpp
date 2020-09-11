#include<bits/stdc++.h>
using namespace std;

int main() {
    int T, N, D, K, S;
    double maxiTime;

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> D >> N;

        maxiTime = 0;
        for (int i = 1; i <= N; i++) {
            cin >> K >> S;
            maxiTime = max(maxiTime, (D - K)/(S * 1.0));
        }

        printf("Case #%d: %.7lf\n", cases, D/maxiTime);
    }
}
