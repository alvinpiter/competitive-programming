#include<bits/stdc++.h>
using namespace std;
#define MAXN 500000
#define BLOCK 720

struct Query {
    int l, r, index;
    Query(int _l, int _r, int _index): l(_l), r(_r), index(_index) {}
};

//Modified Mo's algorithm. The order of right end is increasing, then decreasing, then increasing, so on.
bool cmp(Query a, Query b) {
    int blockA = a.l/BLOCK;
    int blockB = b.l/BLOCK;

    if (blockA != blockB) {
        return blockA < blockB;
    } else {
        if (blockA % 2 == 0)
            return a.r < b.r;
        else
            return a.r > b.r;
    }
}

int n, q, a[MAXN + 3], answer[MAXN + 3];
vector<Query> queries;

/*
cnt[num] -> How many times num appears in current window
sum[b] -> How many integers in block b appears once in current window
*/
int cnt[MAXN + 3], sum[BLOCK + 3], onceCount;
int currentL, currentR;

void add(int num) {
    cnt[num] += 1;
    if (cnt[num] == 1) {
        sum[num/BLOCK] += 1;
        onceCount += 1;
    } else if (cnt[num] == 2) {
        sum[num/BLOCK] -= 1;
        onceCount -= 1;
    }
}

void remove(int num) {
    cnt[num] -= 1;
    if (cnt[num] == 0) {
        sum[num/BLOCK] -= 1;
        onceCount -= 1;
    } else if (cnt[num] == 1) {
        sum[num/BLOCK] += 1;
        onceCount += 1;
    }
}

int getOneOccurence() {
    //Find which block contains a number that appears once and then iterate the range of numbers.\

    if (onceCount == 0)
        return 0;

    int result = 0;
    for (int b = 0; b <= BLOCK; b++) {
        if (sum[b] > 0) {
            for (int i = b * BLOCK; i < (b + 1) * BLOCK; i++) {
                if (cnt[i] == 1) {
                    result = i;
                    break;
                }
            }

            break;
        }
    }

    return result;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);

        queries.push_back(Query(l, r, i));
    }

    sort(queries.begin(), queries.end(), cmp);

    memset(cnt, 0, sizeof(cnt));
    memset(sum, 0, sizeof(sum));
    onceCount = 0;

    currentL = 1;
    currentR = 0;
    for (auto query: queries) {
        int l = query.l;
        int r = query.r;
        int index = query.index;

        while (currentR < r) {
            currentR += 1;
            add(a[currentR]);
        }

        while (currentR > r) {
            remove(a[currentR]);
            currentR -= 1;
        }

        while (currentL < l) {
            remove(a[currentL]);
            currentL += 1;
        }

        while (currentL > l) {
            currentL -= 1;
            add(a[currentL]);
        }

        answer[index] = getOneOccurence();
    }

    for (int i = 1; i <= q; i++)
        printf("%d\n", answer[i]);
}
