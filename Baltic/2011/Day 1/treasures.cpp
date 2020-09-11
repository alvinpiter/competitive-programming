#include<bits/stdc++.h>
using namespace std;
#define MAXN 700
#define INF 1000000

int N, M, rViking, cViking, rShip, cShip, rTreasure, cTreasure;
int dViking[MAXN + 3][MAXN + 3], minDViking[MAXN + 3][MAXN + 3], dShip[MAXN + 3][MAXN + 3];
char grid[MAXN + 3][MAXN + 3];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void reset() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            dViking[i][j] = minDViking[i][j] = dShip[i][j] = INF;
        }
    }
}

bool isInsideGrid(int r, int c) {
    return (r >= 1 && r <= N && c >= 1 && c <= M);
}

void calculateViking() {
    queue<int> qr, qc;

    dViking[rViking][cViking] = 0;
    qr.push(rViking); qc.push(cViking);
    while (!qr.empty()) {
        int ur = qr.front(), uc = qc.front();
        qr.pop();
        qc.pop();

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir];
            int vc = uc + dc[dir];

            if (!isInsideGrid(vr, vc)) continue;
            if (grid[vr][vc] == 'I') continue;

            if (dViking[vr][vc] == INF) {
                dViking[vr][vc] = dViking[ur][uc] + 1;
                qr.push(vr);
                qc.push(vc);
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == 'I') continue;

            for (int r = i; r <= N && grid[r][j] != 'I'; r++)
                minDViking[i][j] = min(minDViking[i][j], dViking[r][j]);

            for (int r = i; r >= 1 && grid[r][j] != 'I'; r--)
                minDViking[i][j] = min(minDViking[i][j], dViking[r][j]);

            for (int c = j; c <= M && grid[i][c] != 'I'; c++)
                minDViking[i][j] = min(minDViking[i][j], dViking[i][c]);

            for (int c = j; c >= 1 && grid[i][c] != 'I'; c--)
                minDViking[i][j] = min(minDViking[i][j], dViking[i][c]);
        }
    }
}

void calculateShip() {
    queue<int> qr, qc;

    dShip[rShip][cShip] = 0;
    qr.push(rShip); qc.push(cShip);
    while (!qr.empty()) {
        int ur = qr.front(), uc = qc.front();
        qr.pop(); qc.pop();

        for (int dir = 0; dir < 4; dir++) {
            int vr = ur + dr[dir];
            int vc = uc + dc[dir];

            if (!isInsideGrid(vr, vc)) continue;
            if (grid[vr][vc] == 'I') continue;
            if (minDViking[vr][vc] <= dShip[ur][uc] + 1) continue;

            if (dShip[vr][vc] == INF) {
                dShip[vr][vc] = dShip[ur][uc] + 1;
                qr.push(vr);
                qc.push(vc);
            }
        }
    }
}

int main() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'V') {
                rViking = i;
                cViking = j;
            }

            if (grid[i][j] == 'Y') {
                rShip = i;
                cShip = j;
            }

            if (grid[i][j] == 'T') {
                rTreasure = i;
                cTreasure = j;
            }
        }
    }

    reset();
    calculateViking();
    calculateShip();

    if (dShip[rTreasure][cTreasure] < INF) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}
