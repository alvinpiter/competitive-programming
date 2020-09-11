#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int T, N, M, prefixSum[MAXN + 3], counter[26];
string S;

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> M >> S;

        memset(prefixSum, 0, sizeof(prefixSum));
        memset(counter, 0, sizeof(counter));
        for (int i = 1; i <= M; i++) {
            int p;
            cin >> p;

            prefixSum[1] += 1;
            prefixSum[p + 1] -= 1;
        }

        //final try
        prefixSum[1] += 1;
        prefixSum[N + 1] -= 1;

        for (int i = 1; i <= N; i++)
            prefixSum[i] += prefixSum[i - 1];

        for (int i = 0; i < N; i++) {
            counter[S[i] - 'a'] += prefixSum[i + 1];
        }

        for (int i = 0; i < 26; i++) {
            if (i > 0)
                cout << " ";
            cout << counter[i];
        }
        cout << endl;
    }
}
