#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000
#define LL long long int

int T, N, K, f[MAXN + 3];
string S;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> S >> K;

        N = S.length();

        //Initialize failure function
        f[0] = -1;
        int prevF = f[0];
        for (int i = 1; i <= N; i++) {
            while (prevF != -1 && S[i - 1] != S[prevF])
                prevF = f[prevF];

            f[i] = prevF + 1;
            prevF = f[i];
        }

        LL answer = ((LL) K - 1) * (N - f[N]) + N;

        cout << answer << "\n";
    }
}
