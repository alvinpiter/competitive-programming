#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 3000

int n, m, a, b, mat[MAXN + 3][MAXN + 3];
int miniRow[MAXN + 3][MAXN + 3];
LL x, y, z, g[MAXN * MAXN + 3], answer;

int main() {
    cin >> n >> m >> a >> b;
    cin >> g[0] >> x >> y >> z;

    for (int i = 1; i <= n * m; i++)
        g[i] = (g[i - 1] * x + y)%z;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            mat[i][j] = g[(i - 1) * m + j - 1];
    }

    for (int i = 1; i <= n; i++) {
        deque<int> dq;
        for (int j = 1; j <= m; j++) {
            while (!dq.empty() && dq.front() <= j - b)
                dq.pop_front();

            while (!dq.empty() && mat[i][dq.back()] >= mat[i][j])
                dq.pop_back();

            dq.push_back(j);

            if (j >= b)
                miniRow[i][j - b + 1] = mat[i][dq.front()];
        }
    }

    answer = 0;
    for (int j = 1; j + b - 1 <= m; j++) {
        deque<int> dq;
        for (int i = 1; i <= n; i++) {
            while (!dq.empty() && dq.front() <= i - a)
                dq.pop_front();

            while (!dq.empty() && miniRow[dq.back()][j] >= miniRow[i][j])
                dq.pop_back();

            dq.push_back(i);

            if (i >= a)
                answer += miniRow[dq.front()][j];
        }
    }

    cout << answer << endl;
}
