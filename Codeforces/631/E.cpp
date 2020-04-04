#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN (1 << 22)
#define DEBUG false

int t, h, g, a[MAXN + 3], pos[MAXN + 3];
vector<int> sortedA, answer;

int findEndOfChain(int idx) {
    int leftId = 2 * idx;
    int rightId = 2 * idx + 1;

    if (a[leftId] == 0 && a[rightId] == 0)
        return idx;

    if (a[leftId] > a[rightId])
        return findEndOfChain(leftId);
    else
        return findEndOfChain(rightId);
}

void f(int idx) {
    int leftId = 2 * idx;
    int rightId = 2 * idx + 1;

    if (a[leftId] == 0 && a[rightId] == 0) {
        pos[a[idx]] = 0;
        a[idx] = 0;
        return;
    }

    int idxMax;
    if (a[leftId] > a[rightId]) {
        idxMax = leftId;
    } else if (a[rightId] > a[leftId]) {
        idxMax = rightId;
    }

    pos[a[idxMax]] = idx;
    pos[a[idx]] = idxMax;

    swap(a[idx], a[idxMax]);

    f(idxMax);
}

int main() {
    scanf("%d", &t);

    for (int cases = 1; cases <= t; cases++) {
        scanf("%d%d", &h, &g);

        sortedA.clear();
        answer.clear();
        for (int i = 1; i < (1 << (h + 1)); i++) {
            pos[i] = 0;
            a[i] = 0;
        }

        for (int i = 1; i < (1 << h); i++) {
            scanf("%d", &a[i]);
            pos[a[i]] = i;

            sortedA.push_back(a[i]);
        }

        sort(sortedA.begin(), sortedA.end());

        for (int i = sortedA.size() - 1; i >= 0; i--) {
            int current = pos[sortedA[i]];

            if (current == 0)
                continue;

            int endOfChain = findEndOfChain(current);

            if (endOfChain >= (1 << g)) {
                answer.push_back(current);
                f(current);
            }
        }

        LL total = 0;
        for (int i = 1; i < (1 << g); i++)
            total += a[i];

        printf("%lld\n", total);
        for (auto ans: answer)
            printf("%d ", ans);
        printf("\n");
    }
}
