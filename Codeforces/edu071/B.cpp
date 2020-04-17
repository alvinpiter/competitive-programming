#include<bits/stdc++.h>
using namespace std;

int n, m, A[53][53], B[53][53];
vector<pair<int, int> > steps;

void paint(int r, int c) {
    steps.push_back({r, c});
    B[r][c] = B[r][c + 1] = B[r + 1][c] = B[r + 1][c + 1] = 1;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= m; j++)
            cin >> A[i][j];
    }

    memset(B, 0, sizeof(B));

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            if (A[i][j] == 1 && A[i][j + 1] == 1 && A[i + 1][j] == 1 && A[i + 1][j + 1] == 1) {
                paint(i, j);
            }
        }
    }

    bool valid = true;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (A[i][j] != B[i][j])
                valid = false;
        }
    }

    if (valid) {
        cout << steps.size() << endl;
        for (auto s: steps)
            cout << s.first << " " << s.second << endl;
    } else {
        cout << -1 << endl;
    }
}
