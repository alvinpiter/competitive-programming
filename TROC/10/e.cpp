#include<bits/stdc++.h>
using namespace std;
#define MAXR 500
#define MAXN 250000
#define MAXA 100000
#define MAXQ 100000

struct Query {
    int r, c, strength, index;
    Query() {}
    Query(int _r, int _c, int _strength, int _index) {
        r = _r;
        c = _c;
        strength = _strength;
        index = _index;
    }
};

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int R, C, Q, A[MAXR + 3][MAXR + 3];
int N, parent[MAXN + 3], minDistance[MAXN + 3];
Query queries[MAXQ + 3];
int answer[MAXQ + 3];
vector<pair<int, int> > pos[MAXA + 3];

bool compareByStrength(Query a, Query b) {
    return a.strength < b.strength;
}

int getIndex(int r, int c) {
    return (r - 1) * C + c;
}

int findSet(int x) {
    return (parent[x] == x ? x : parent[x] = findSet(parent[x]));
}

void joinSet(int x, int y) {
    int px = findSet(x);
    int py = findSet(y);

    parent[py] = px;
    minDistance[px] = min(minDistance[px], minDistance[py]);
}

//Connect node at (r, c) to all it's neighbors whose value is at most threshold.
void expand(int r, int c, int threshold) {
    for (int dir = 0; dir < 4; dir++) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];

        if (nr >= 1 && nr <= R && nc >= 1 && nc <= C && A[nr][nc] <= threshold) {
            joinSet(getIndex(r, c), getIndex(nr, nc));
        }
    }
}

int main() {
    scanf("%d%d%d", &R, &C, &Q);

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf("%d", &A[i][j]);
            pos[A[i][j]].push_back(make_pair(i, j));

            parent[getIndex(i, j)] = getIndex(i, j);
            minDistance[getIndex(i, j)] = (i - 1) + (j - 1);
        }
    }

    for (int i = 1; i <= Q; i++) {
        int r, c, s;
        scanf("%d%d%d", &r, &c, &s);

        queries[i] = Query(r, c, s, i);
    }

    sort(queries + 1, queries + Q + 1, compareByStrength);

    int ptr = 1;
    for (int i = 1; i <= Q; i++) {
        while (ptr <= queries[i].strength) {
            for (int j = 0; j < pos[ptr].size(); j++) {
                pair<int, int> coor = pos[ptr][j];
                expand(coor.first, coor.second, queries[i].strength);
            }

            ptr += 1;
        }

        int qr = queries[i].r;
        int qc = queries[i].c;
        int qIndex = queries[i].index;

        answer[qIndex] = minDistance[findSet(getIndex(qr, qc))];
    }

    for (int i = 1; i <= Q; i++)
        printf("%d\n", answer[i]);
}
