#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define MAXLG 29

int N, M, L[103], R[103], nxt[MAXN + 3][MAXLG + 3], K, answer[MAXN + 3];

void initializeNxt() {
    int temp[MAXN + 3];
    for (int i = 1; i <= N; i++)
        temp[i] = i;

    for (int i = 1; i <= M; i++) {
        int l = L[i], r = R[i];
        while (r > l) {
            swap(temp[l], temp[r]);
            l += 1;
            r -= 1;
        }
    }

    for (int i = 1; i <= N; i++)
        nxt[temp[i]][0] = i;

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            nxt[i][lg] = nxt[nxt[i][lg - 1]][lg - 1];
        }
    }
}

int main() {
    freopen("swap.in", "r", stdin);
    freopen("swap.out", "w", stdout);

    cin >> N >> M >> K;
    for (int i = 1; i <= M; i++)
        cin >> L[i] >> R[i];

    initializeNxt();

    for (int i = 1; i <= N; i++) {
        int curr = i;
        for (int lg = 0; lg <= MAXLG; lg++) {
            if (K & (1 << lg))
                curr = nxt[curr][lg];
        }

        answer[curr] = i;
    }

    for (int i = 1; i <= N; i++)
        cout << answer[i] << endl;
}
