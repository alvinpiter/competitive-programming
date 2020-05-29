#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define BLOCK 350
#define MAXN 100000
#define MAXA 2000000

struct Query {
    int l, r, index;
    Query(int _l, int _r, int _index): l(_l), r(_r), index(_index) {}
};

bool cmp(Query a, Query b) {
    if (a.l/BLOCK != b.l/BLOCK)
        return a.l/BLOCK < b.l/BLOCK;
    else
        return a.r < b.r;
}

int n, m, k, prefix[MAXN + 3], cnt[MAXA + 3];
int currentL, currentR;
LL currentAnswer, answer[MAXN + 3];
vector<Query> queries;

void add(int idx) {
    currentAnswer += cnt[k^prefix[idx]];
    cnt[prefix[idx]] += 1;
}

void remove(int idx) {
    cnt[prefix[idx]] -= 1;
    currentAnswer -= cnt[k^prefix[idx]];
}

int main() {
    scanf("%d%d%d", &n, &m, &k);

    prefix[0] = 0;
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d", &a);

        prefix[i] = prefix[i - 1]^a;
    }

    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries.push_back(Query(l, r, i));
    }

    sort(queries.begin(), queries.end(), cmp);

    memset(cnt, 0, sizeof(cnt));

    currentL = 0;
    currentR = -1;
    currentAnswer = 0;
    for (auto query: queries) {
        int l = query.l;
        int r = query.r;
        int index = query.index;

        while (currentR < r) {
            currentR += 1;
            add(currentR);
        }

        while (currentR > r) {
            remove(currentR);
            currentR -= 1;
        }

        while (currentL > l - 1) {
            currentL -= 1;
            add(currentL);
        }

        while (currentL < l - 1) {
            remove(currentL);
            currentL += 1;
        }

        answer[index] = currentAnswer;
    }

    for (int i = 1; i <= m; i++)
        printf("%lld\n", answer[i]);
}
