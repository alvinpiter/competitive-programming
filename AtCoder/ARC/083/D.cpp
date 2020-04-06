#include<bits/stdc++.h>
using namespace std;
#define MAXN 300

int N, d[MAXN + 3][MAXN + 3];

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cin >> d[i][j];
    }

    long long int answer = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            bool isNeeded = true;
            for (int k = 1; k <= N; k++) {
                if (k == i || k == j)
                    continue;

                if (d[i][j] > d[i][k] + d[k][j]) {
                    cout << -1 << endl;
                    return 0;
                }

                if (d[i][j] == d[i][k] + d[k][j])
                    isNeeded = false;
            }

            if (isNeeded)
                answer += d[i][j];
        }
    }

    cout << answer << endl;
}
