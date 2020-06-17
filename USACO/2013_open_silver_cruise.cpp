#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000
#define MAXLG 29

int N, M, K, lef[MAXN + 3], rig[MAXN + 3], nxt[MAXN + 3][MAXLG + 3];
string directions[MAXN + 3];

int main() {
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++)
        cin >> lef[i] >> rig[i];

    for (int i = 1; i <= M; i++)
        cin >> directions[i];

    for (int i = 1; i <= N; i++) {
        //simulate one cycle
        int current = i;
        for (int j = 1; j <= M; j++) {
            if (directions[j] == "L")
                current = lef[current];
            else
                current = rig[current];
        }

        nxt[i][0] = current;
    }

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++)
            nxt[i][lg] = nxt[nxt[i][lg - 1]][lg - 1];
    }

    int current = 1;
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (K & (1 << lg))
            current = nxt[current][lg];
    }

    cout << current << endl;
}
