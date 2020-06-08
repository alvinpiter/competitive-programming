#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000
#define BLOCK 350

int N, id[MAXN + 3];
int currentL, currentR, cntSingle, cnt[MAXN + 3];
vector<int> pos[MAXN + 3];
vector<pair<int, int> > queries;
LL answer;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first/BLOCK != b.first/BLOCK)
        return a.first/BLOCK < b.first/BLOCK;
    else
        return a.second < b.second;
}

void add(int num) {
    cnt[num] += 1;
    if (cnt[num] == 1)
        cntSingle += 1;
    if (cnt[num] > 1)
        cntSingle -= 1;
}

void remove(int num) {
    cnt[num] -= 1;
    if (cnt[num] == 0)
        cntSingle -= 1;
    if (cnt[num] == 1)
        cntSingle += 1;
}

int main() {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    scanf("%d", &N);
    for (int i = 1; i <= 2 * N; i++) {
        scanf("%d", &id[i]);
        pos[id[i]].push_back(i);
    }

    for (int i = 1; i <= N; i++)
        queries.push_back({pos[i][0], pos[i][1]});

    sort(queries.begin(), queries.end(), cmp);

    memset(cnt, 0, sizeof(cnt));
    cntSingle = 0;
    answer = 0;
    currentL = 1;
    currentR = 0;
    for (auto query: queries) {
        int l = query.first, r = query.second;

        while (currentR < r) {
            add(id[currentR + 1]);
            currentR += 1;
        }

        while (currentR > r) {
            remove(id[currentR]);
            currentR -= 1;
        }

        while (currentL < l) {
            remove(id[currentL]);
            currentL += 1;
        }

        while (currentL > l) {
            add(id[currentL - 1]);
            currentL -= 1;
        }

        answer += cntSingle;
    }

    printf("%lld\n", answer/2);
}
