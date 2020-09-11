#include<bits/stdc++.h>
using namespace std;
#define MAXN 50

int n, m;
bool visited[MAXN + 3][MAXN + 3];
char grid[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void DFS(int r, int c) {
    visited[r][c] = true;

    for (int dir = 0; dir < 4; dir++) {
        int vr = r + dr[dir], vc = c + dc[dir];

        if (vr >= 1 && vr <= n && vc >= 1 && vc <= m && !visited[vr][vc] && grid[vr][vc] != '#')
            DFS(vr, vc);
    }
}

int countNumCC() {
    memset(visited, false, sizeof(visited));

    int numCC = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '.' && !visited[i][j]) {
                numCC += 1;
                DFS(i, j);
            }
        }
    }

    return numCC;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cin >> grid[i][j];
    }

    if (countNumCC() != 1) {
        cout << "Impossible\n";
        return 0;
    }

    //If these question marks are not visited, then it must be #
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '?' && !visited[i][j])
                grid[i][j] = '#';
        }
    }

    /*
    Up until now, all ? will be connected with at least one .
    We try changing it into #. If numCC is still one, then the answer is Ambiguous
    */
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '?') {
                grid[i][j] = '#';
                if (countNumCC() == 1) {
                    cout << "Ambiguous\n";
                    return 0;
                }
                grid[i][j] = '?';
            }
        }
    }

    //Answer is unique
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (grid[i][j] == '?')
                cout << '.';
            else
                cout << grid[i][j];
        }
        cout << endl;
    }
}
