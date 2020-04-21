#include<bits/stdc++.h>
using namespace std;
#define MAXN 300000

int q, b, w;
bool visited[7][MAXN + 3];
vector<pair<int, int> > answer;
vector<pair<int, int> > pos;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

int main() {
    scanf("%d", &q);
    for (int cases = 1; cases <= q; cases++) {
        scanf("%d%d", &b, &w);

        int tempB = min(b, w);
        int tempW = max(b, w);

        if (tempW < tempB - 1 || tempW > 3 * tempB + 1) {
            printf("NO\n");
        } else {
            //build chain
            for (int rep = 1; rep <= tempB; rep++) {
                int r = 3;
                int c = 2 * rep;

                visited[r][c] = true;
                answer.push_back({r, c});

                if (rep < tempB) {
                    visited[r][c + 1] = true;
                    answer.push_back({r, c + 1});
                }

                pos.push_back({r, c});
            }

            tempW = tempW - (tempB - 1);
            tempB = 0;

            //relax if needed
            for (auto p: pos) {
                int r = p.first, c = p.second;
                for (int dir = 0; dir < 4 && tempW > 0; dir++) {
                    int nr = r + dr[dir], nc = c + dc[dir];
                    if (visited[nr][nc] == false) {
                        visited[nr][nc] = true;
                        answer.push_back({nr, nc});

                        tempW -= 1;
                    }
                }
            }

            //hack
            if (b > w) {
                for (int i = 0; i < (int) answer.size(); i++)
                    answer[i].first -= 1;
            }

            printf("YES\n");
            for (auto p: answer)
                printf("%d %d\n", p.first, p.second);

            //clean up
            answer.clear();
            pos.clear();
            for (int i = 1; i <= 5; i++) {
                for (int j = 1; j <= 2 * max(b, w); j++)
                    visited[i][j] = false;
            }
        }
    }
}
