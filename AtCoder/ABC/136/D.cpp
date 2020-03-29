#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

string S;
int N, consL[MAXN + 3], consR[MAXN + 3], ans[MAXN + 3];

int main() {
    cin >> S;
    N = S.length();

    consL[N] = 0;
    for (int i = N - 1; i >= 0; i--) {
        if (S[i] == 'L')
            consL[i] = consL[i + 1] + 1;
        else
            consL[i] = 0;
    }

    consR[0] = 1;
    for (int i = 1; i < N; i++) {
        if (S[i] == 'R')
            consR[i] = consR[i - 1] + 1;
        else
            consR[i] = 0;
    }

    memset(ans, 0, sizeof(ans));
    for (int i = 0; i < N - 1; i++) {
        if (S[i] == 'R' && S[i + 1] == 'L') {
            ans[i] = (consR[i] + 1)/2 + consL[i + 1]/2;
            ans[i + 1] = consR[i]/2 + (consL[i + 1] + 1)/2;
        }
    }

    for (int i = 0; i < N; i++)
        cout << ans[i] << " ";

    cout << endl;
}
