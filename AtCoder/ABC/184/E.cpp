#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXH 2000

/*
Modified BFS.
Process nodes starting from the one closest to S.
Assume we are currently processing all nodes that are at distance d from S.
Let T be a set of all teleports that exist at distance d from S.

For each element t of T, do:
* Find the position of all nodes whose character is t and distance > d, then update the distance to d + 1.

*/

int H, W, dist[MAXH + 3][MAXH + 3], startR, startC, goalR, goalC;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
bool seen[26];
char grid[MAXH + 3][MAXH + 3];
vector<pair<int, int> > pos[26];
vector<pair<int, int> > atDist[MAXH * MAXH];

bool isalpha(char c) {
    return c >= 'a' && c <= 'z';
}

int main() {
    cin >> H >> W;
    for (int i = 1; i <= H; i++) {
        for (int j = 1; j <= W; j++) {
            cin >> grid[i][j];
            if (isalpha(grid[i][j])) {
                pos[grid[i][j] - 'a'].push_back(make_pair(i, j));
            }

            if (grid[i][j] == 'S') {
                startR = i; startC = j;
            }

            if (grid[i][j] == 'G') {
                goalR = i; goalC = j;
            }
        }
    }

    memset(seen, false, sizeof(seen));
    memset(dist, -1, sizeof(dist));

    dist[startR][startC] = 0;

    atDist[0].push_back(make_pair(startR, startC));

    for (int d = 0; d < MAXH * MAXH ; d++) {
        vector<int> firstTimer;

        for (int i = 0; i < (int) atDist[d].size(); i++) {
            int ur = atDist[d][i].first;
            int uc = atDist[d][i].second;

            if (isalpha(grid[ur][uc]) && seen[grid[ur][uc] - 'a'] == false) {
                firstTimer.push_back(grid[ur][uc] - 'a');
                seen[grid[ur][uc] - 'a'] = true;
            }

            for (int dir = 0; dir < 4; dir++) {
                int vr = ur + dr[dir];
                int vc = uc + dc[dir];

                if (vr < 1 || vr > H || vc < 1 || vc > W) {
                    continue;
                }

                if (grid[vr][vc] == '#' || dist[vr][vc] != -1) {
                    continue;
                }

                dist[vr][vc] = dist[ur][uc] + 1;
                atDist[dist[vr][vc]].push_back(make_pair(vr, vc));
            }
        }

        for (int i = 0; i < (int) firstTimer.size(); i++) {
            int charIndex = firstTimer[i];
            for (int j = 0; j < (int) pos[charIndex].size(); j++) {
                int r = pos[charIndex][j].first;
                int c = pos[charIndex][j].second;

                if (dist[r][c] == -1) {
                    dist[r][c] = d + 1;
                    atDist[dist[r][c]].push_back(make_pair(r, c));
                }
            }
        }
    }

    cout << dist[goalR][goalC] << endl;
}
