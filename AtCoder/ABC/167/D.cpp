#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000
#define MAXLG 63

int N, nxt[MAXN + 3][MAXLG + 3];
LL K;

int main() {
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
        cin >> nxt[i][0];

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 1; i <= N; i++) {
            nxt[i][lg] = nxt[nxt[i][lg - 1]][lg - 1];
        }
    }

    int current = 1;
    for (int lg = 0; lg <= MAXLG; lg++) {
        if (K & (1LL << lg))
            current = nxt[current][lg];
    }

    cout << current << endl;
}
