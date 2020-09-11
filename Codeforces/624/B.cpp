#include<bits/stdc++.h>
using namespace std;
#define MAXN 100

int T, N, M, A[MAXN + 3], rightOf[MAXN + 3];

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N >> M;
        for (int i = 1; i <= N; i++)
            cin >> A[i];

        memset(rightOf, -1, sizeof(rightOf));
        for (int i = 1; i <= M; i++) {
            int p;
            cin >> p;

            rightOf[p] = p + 1;
        }

        for (int i = 1; i <= N;) {
            int j = i;
            while (rightOf[j] != -1)
                j = rightOf[j];

            sort(A + i, A + j + 1);

            i = j + 1;
        }
        bool sorted = true;
        for (int i = 2; i <= N; i++) {
            if (A[i] < A[i - 1])
                sorted = false;
        }

        if (sorted)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
}
