#include<bits/stdc++.h>
using namespace std;
#define MAXK 100000

int N, K, answer[MAXK + 3], leftOver;

int main() {
    cin >> N >> K;

    leftOver = N;
    for (int i = 1; i <= K; i++) {
        answer[i] = i;
        leftOver -= i;

        if (leftOver < 0) {
            cout << "NO\n";
            return 0;
        }
    }

    for (int i = 1; i <= K; i++)
        answer[i] += leftOver/K;

    leftOver %= K;

    if (leftOver > 0) {
        if (K == 1) {
            //Nothing to check, because it is always possible
        } else if (K == 2) {
            if (leftOver == 1) {
                answer[2] += 1;
                if (answer[1] * 2 < answer[2]) {
                    cout << "NO\n";
                    return 0;
                }
            }
        } else if (K == 3) {
            if (N == 8) {
                cout << "NO\n";
                return 0;
            } else answer[3] += leftOver;
        } else {
            int addToK = max(1, leftOver - 1);
            answer[K] += addToK;
            answer[K - 1] += leftOver - addToK;
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= K; i++)
        cout << answer[i] << " ";
    cout << endl;
}
