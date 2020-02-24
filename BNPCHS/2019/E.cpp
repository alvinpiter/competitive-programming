#include<bits/stdc++.h>
using namespace std;
#define MAXN 10000

int T, N, M;
string steps;

int main() {
    cin >>T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        M = 0;
        while ((M * M + M)/2 < N || ((M*M + M)/2 - N)%2 == 1)
            M += 1;

        steps = "";
        for (int i = 1; i <= M; i++)
            steps += '+';

        int rem = (M * M + M)/2 - N;
        for (int i = M; i >= 1; i--) {
            if (rem >= 2 * i) {
                rem -= 2 * i;
                steps[M - i] = '-';
            }
        }

        cout << "Case #" << cases << ": " << M << " " << steps << endl;
    }
}
