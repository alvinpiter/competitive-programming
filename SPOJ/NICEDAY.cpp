#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define INF 1000000000

int T, N, BIT[MAXN + 3], answer;
vector<pair<int, pair<int, int> > > triples;

void update(int idx, int value) {
    while (idx <= MAXN) {
        BIT[idx] = min(BIT[idx], value);
        idx += (idx & -idx);
    }
}

int query(int idx) {
    int result = INF;
    while (idx > 0) {
        result = min(result, BIT[idx]);
        idx -= (idx & -idx);
    }

    return result;
}

int main() {
    scanf("%d", &T);
    for (int cases = 1; cases <= T; cases++) {
        answer = 0;
        triples.clear();
        for (int i = 1; i <= MAXN; i++)
            BIT[i] = INF;

        scanf("%d", &N);
        for (int i = 1; i <= N; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);

            triples.push_back(make_pair(a, make_pair(b, c)));
        }

        sort(triples.begin(), triples.end());

        for (int i = 0; i < N; i++) {
            int x = triples[i].second.first;
            int y = triples[i].second.second;

            if (query(x - 1) > y)
                answer += 1;

            update(x, y);
        }

        printf("%d\n", answer);
    }
}
