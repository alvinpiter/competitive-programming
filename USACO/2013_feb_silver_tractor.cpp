#include<bits/stdc++.h>
using namespace std;
#define MAXN 500

int N, grid[MAXN + 3][MAXN + 3];
bool visited[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int DFS(int ur, int uc, int threshold) {
    visited[ur][uc] = true;

    int cnt = 1;
    for (int dir = 0; dir < 4; dir++) {
        int vr = ur + dr[dir], vc = uc + dc[dir];
        if (vr >= 1 && vr <= N && vc >= 1 && vc <= N && abs(grid[vr][vc] - grid[ur][uc]) <= threshold && !visited[vr][vc]) {
            cnt += DFS(vr, vc, threshold);
        }
    }

    return cnt;
}

int findLargestCC(int threshold) {
    memset(visited, false, sizeof(visited));

    int largest = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (!visited[i][j]) {
                largest = max(largest, DFS(i, j, threshold));
            }
        }
    }

    return largest;
}

int main() {
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++)
            cin >> grid[i][j];
    }

    int lo = 0, hi = 1000000000, mid;
    while (hi >= lo) {
        mid = (lo + hi)/2;
        if (findLargestCC(mid) >= (N*N + 1)/2)
            hi = mid - 1;
        else
            lo = mid + 1;
    }

    cout << lo << endl;
}
