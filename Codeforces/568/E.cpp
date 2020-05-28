#include<bits/stdc++.h>
using namespace std;
#define MAXN 2000

/*
Implementation problem

Iterate from characters from z to a
* If current character does not appear in the grid, use previous character position
* If current character appears in the grid:
    * Make sure all are on the same row or all are on the same column
    * Make sure character in between current character position are larger than current character
*/

int t, n, m;
char grid[MAXN + 3][MAXN + 3];
vector<pair<int, int> > pos[26], answer1, answer2;

int main() {
    cin >> t;
    for (int cases = 1; cases <= t; cases++) {
        cin >> n >> m;

        //reset everything
        answer1.clear();
        answer2.clear();
        for (int c = 0; c < 26; c++)
            pos[c].clear();

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                cin >> grid[i][j];

                if (grid[i][j] != '.')
                    pos[grid[i][j] - 'a'].push_back({i, j});
            }
        }

        bool possible = true;
        for (int c = 25; c >= 0 && possible; c--) {
            if (pos[c].empty()) {
                if (answer1.empty())
                    continue;
                else {
                    answer1.push_back(answer1.back());
                    answer2.push_back(answer2.back());
                }
            } else {
                sort(pos[c].begin(), pos[c].end());

                bool isOnSameRow = true;
                bool isOnSameColumn = true;

                for (int i = 1; i < pos[c].size(); i++) {
                    if (pos[c][i].first != pos[c][0].first)
                        isOnSameRow = false;

                    if (pos[c][i].second != pos[c][0].second)
                        isOnSameColumn = false;
                }

                if (!isOnSameRow && !isOnSameColumn) {
                    possible = false;
                    break;
                }

                if (isOnSameRow) {
                    for (int i = 1; i < pos[c].size(); i++) {
                        for (int col = pos[c][i - 1].second + 1; col < pos[c][i].second; col++) {
                            if (grid[pos[c][0].first][col] - 'a' < c) {
                                possible = false;
                                break;
                            }
                        }
                    }
                } else if (isOnSameColumn) {
                    for (int i = 1; i < pos[c].size(); i++) {
                        for (int row = pos[c][i - 1].first + 1; row < pos[c][i].first; row++) {
                            if (grid[row][pos[c][0].second] -'a' < c) {
                                possible = false;
                                break;
                            }
                        }
                    }
                }

                if (possible) {
                    answer1.push_back(pos[c][0]);
                    answer2.push_back(pos[c].back());
                }
            }
        }

        if (possible) {
            cout << "YES\n";
            cout << (int) answer1.size() << endl;
            for (int i = (int) answer1.size() - 1; i >= 0; i--)
                cout << answer1[i].first << " " << answer1[i].second << " " << answer2[i].first << " " << answer2[i].second << endl;
        } else {
            cout << "NO\n";
        }
    }
}
