#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000
#define SQRT 350

int n, m, a[MAXN + 3], answer[MAXN + 3], cnt[MAXN + 3];
pair<pair<int, int>, int > queries[MAXN + 3];
int currentAnswer = 0;

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first.first/SQRT != b.first.first/SQRT)
        return a.first.first/SQRT < b.first.first/SQRT;
    else
        return a.first.second < b.first.second;
}

void add(int idx) {
    if (a[idx] > MAXN) return;

    if (cnt[a[idx]] == a[idx])
        currentAnswer -= 1;
    else if (cnt[a[idx]] == a[idx] - 1)
        currentAnswer += 1;

    cnt[a[idx]] += 1;
}

void remove(int idx) {
    if (a[idx] > MAXN) return;

    if (cnt[a[idx]] == a[idx])
        currentAnswer -= 1;
    else if (cnt[a[idx]] == a[idx] + 1)
        currentAnswer += 1;

    cnt[a[idx]] -= 1;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        queries[i] = {{l, r}, i};
    }

    sort(queries + 1, queries + m + 1, cmp);

    int currentL = 1, currentR = 0;

    memset(cnt, 0, sizeof(cnt));
    for (int q = 1; q <= m; q++) {
        int targetL = queries[q].first.first, targetR = queries[q].first.second, queryIdx = queries[q].second;

        while (currentL < targetL) {
            remove(currentL);
            currentL += 1;
        }

        while (currentL > targetL) {
            add(currentL - 1);
            currentL -= 1;
        }

        while (currentR < targetR) {
            add(currentR + 1);
            currentR += 1;
        }

        while (currentR > targetR) {
            remove(currentR);
            currentR -= 1;
        }

        answer[queryIdx] = currentAnswer;
    }

    for (int i = 1; i <= m; i++)
        printf("%d\n", answer[i]);
}
