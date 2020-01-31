#include<bits/stdc++.h>
using namespace std;
#define MAXN 50
#define INF 1000000

int N, h[MAXN + 3][MAXN + 3], startR, startC, answer;
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
bool visited[MAXN + 3][MAXN + 3];
char grid[MAXN + 3][MAXN + 3];
vector<int> heights;

void DFS(int r, int c, int mini, int maxi) {
    visited[r][c] = true;
    for (int dir = 0; dir < 8; dir++) {
        int nextR = r + dr[dir];
        int nextC = c + dc[dir];

        if (nextR < 1 || nextR > N || nextC < 1 || nextC > N)
            continue;

        if (visited[nextR][nextC])
            continue;

        if (h[nextR][nextC] < mini || h[nextR][nextC] > maxi)
            continue;

        DFS(nextR, nextC, mini, maxi);
    }
}

bool checkValidity(int lo, int hi) {
    if (h[startR][startC] < lo || h[startR][startC] > hi)
        return false;

    memset(visited, false, sizeof(visited));
    DFS(startR, startC, lo, hi);

    bool valid = true;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (grid[i][j] == 'F' && !visited[i][j])
                valid = false;
        }
    }

    return valid;
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') {
                startR = i;
                startC = j;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> h[i][j];
            heights.push_back(h[i][j]);
        }
    }

    sort(heights.begin(), heights.end());

    answer = INF;
    for (int i = 0; i < heights.size(); i++) {
        int lo = i, hi = heights.size() - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (checkValidity(heights[i], heights[mid]))
                hi = mid - 1;
            else
                lo = mid + 1;
        }

        if (lo < heights.size())
            answer = min(answer, heights[lo] - heights[i]);
    }

    cout << answer << endl;
}
