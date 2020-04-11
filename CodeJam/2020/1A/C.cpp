#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define LL long long int

int T;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        int R, C;
        scanf("%d%d", &R, &C);

        LL sumOfSkills = 0;

        int grid[R + 3][C + 3];
        bool removed[R + 3][C + 3];
        pair<int, int> neighbor[R + 3][C + 3][4];

        memset(grid, 0, sizeof(grid));
        memset(removed, false, sizeof(removed));
        for (int i = 1; i <= R; i++) {
            for (int j = 1; j <= C; j++) {
                scanf("%d", &grid[i][j]);

                sumOfSkills += grid[i][j];

                for (int dir = 0; dir < 4; dir++)
                    neighbor[i][j][dir] = {i + dr[dir], j + dc[dir]};
            }
        }

        set<pair<int, int> > eliminationList;
        set<pair<int, int> > checkList;

        LL answer = 0;
        for (int iteration = 1; ; iteration++) {
            answer += sumOfSkills;

            checkList.clear();
            if (iteration == 1) {
                for (int i = 1; i <= R; i++) {
                    for (int j = 1; j <= C; j++)
                        checkList.insert({i, j});
                }
            } else {
                for (auto p: eliminationList) {
                    int r = p.first;
                    int c = p.second;

                    for (int dir = 0; dir < 4; dir++) {
                        int nextR = neighbor[r][c][dir].first;
                        int nextC = neighbor[r][c][dir].second;

                        if (nextR >= 1 && nextR <= R && nextC >= 1 && nextC <= C  && !removed[nextR][nextC])
                            checkList.insert({nextR, nextC});
                    }
                }
            }

            eliminationList.clear();
            for (auto p: checkList) {
                int r = p.first;
                int c = p.second;

                int neighborSum = 0;
                int neighborCount = 0;
                for (int dir = 0; dir < 4; dir++) {
                    int nextR = neighbor[r][c][dir].first;
                    int nextC = neighbor[r][c][dir].second;

                    if (nextR >= 1 && nextR <= R && nextC >= 1 && nextC <= C) {
                        neighborSum += grid[nextR][nextC];
                        neighborCount += 1;
                    }
                }

                if (neighborCount > 0) {
                    if (grid[r][c] * neighborCount < neighborSum) {
                        eliminationList.insert({r, c});
                    }
                }
            }

            if (eliminationList.empty())
                break;

            for (auto p: eliminationList) {
                int r = p.first;
                int c = p.second;

                removed[r][c] = true;
                sumOfSkills -= grid[r][c];

                for (int dir = 0; dir < 4; dir++) {
                    int nextR = neighbor[r][c][dir].first;
                    int nextC = neighbor[r][c][dir].second;

                    neighbor[nextR][nextC][(dir + 2)%4] = neighbor[r][c][(dir + 2)%4];
                }
            }
        }

        printf("Case #%d: %lld\n", cases, answer);
    }
}
