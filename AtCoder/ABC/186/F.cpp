#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 200000

int ft[MAXN + 3];

void update(int idx, int val) {
    while (idx <= MAXN) {
        ft[idx] += val;
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = 0;
    while (idx > 0) {
        result += ft[idx];
        idx -= (idx & -idx);
    }

    return result;
}

int H, W, N, firstBlockRight, firstBlockBelow;
vector<int> blockAtColumn[MAXN + 3];
bool seen[MAXN + 3];
LL answer;

int main() {
    scanf("%d%d%d", &H, &W, &N);

    firstBlockRight = W + 1;
    firstBlockBelow = H + 1;
    for (int i = 1; i <= N; i++) {
        int row, col;
        scanf("%d%d", &row, &col);

        if (row == 1) {
            firstBlockRight = min(firstBlockRight, col);
        }

        if (col == 1) {
            firstBlockBelow = min(firstBlockBelow, row);
        }

        blockAtColumn[col].push_back(row);
    }

    memset(ft, 0, sizeof(ft));
    memset(seen, false, sizeof(seen));

    answer = 0;
    for (int col = 1; col <= W; col++) {
        sort(blockAtColumn[col].begin(), blockAtColumn[col].end());

        for (auto row: blockAtColumn[col]) {
            if (!seen[row]) {
                seen[row] = true;
                update(row, 1);
            }
        }

        if (col < firstBlockRight) {
            if (blockAtColumn[col].empty()) {
                answer += H;
            } else {
                int r = blockAtColumn[col][0];
                if (r < firstBlockBelow) {
                    int cntBlocked = query(firstBlockBelow - 1) - query(r - 1);
                    answer += (firstBlockBelow - 1 - cntBlocked);
                } else {
                    answer += (r - 1);
                }
            }
        } else {
            int cntBlocked = query(firstBlockBelow - 1);
            answer += (firstBlockBelow - 1 - cntBlocked);
        }
    }

    printf("%lld\n", answer);
}
