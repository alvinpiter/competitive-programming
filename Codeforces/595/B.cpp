#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int T, N, p[MAXN + 3], numComponent, num[MAXN + 3], counter[MAXN + 3];

void DFS(int u) {
    num[u] = numComponent;
    if (num[p[u]] == -1)
        DFS(p[u]);
}

int main() {
    cin >> T;
    for (int cases = 1; cases <= T; cases++) {
        cin >> N;

        numComponent = 0;
        for (int i = 1; i <= N; i++) {
            num[i] = -1;
            counter[i] = 0;
        }

        for (int i = 1; i <= N; i++)
            cin >> p[i];

        for (int i = 1; i <= N; i++) {
            if (num[i] == -1) {
                numComponent += 1;
                DFS(i);
            }
        }

        for (int i = 1; i <= N; i++) {
            counter[num[i]] += 1;
        }

        for (int i = 1; i <= N; i++)
            cout << counter[num[i]] << " ";

        cout << endl;
    }
}
