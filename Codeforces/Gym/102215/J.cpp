#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 500000

/*
Imagine two jedis i and j. If i is turned into dark side, how can i win against j?
i must invest all its parameter such that it won against j's lowest two parameter.
WLOG, let's say j's lowest two parameter is aj and bj.

ai + c1' >= aj + 1
bi + c2' >= bj + 1

Where c1' + c2' = ci (we invest all ci to ai and bi).
Fromt those two ineq, we get:
ai + bi + ci >= aj + bj + 2

For each i, we can find j with binary search.
*/

struct Jedi {
    int a, b, c, index;
    Jedi(int _a, int _b, int _c, int _index): a(_a), b(_b), c(_c), index(_index) {}
    int sumOfTwoLowestParams() {
        return min(a + b, min(a + c, b + c));
    }
};

bool cmp(Jedi a, Jedi b) {
    return a.sumOfTwoLowestParams() < b.sumOfTwoLowestParams();
}

int main() {
    int n, answer[MAXN + 3];
    vector<Jedi> jedis;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);

        jedis.push_back(Jedi(a, b, c, i));
    }

    sort(jedis.begin(), jedis.end(), cmp);

    for (int i = 0; i < n; i++) {
        LL target = min((LL) jedis[i].a + jedis[i].b + jedis[i].c - 2, (LL) 2e9 + 10);

        int lo = 0, hi = n - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (jedis[mid].sumOfTwoLowestParams() <= target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        int cnt = hi + 1;
        if (jedis[i].sumOfTwoLowestParams() <= target)
            cnt -= 1;

        answer[jedis[i].index] = cnt;
    }

    for (int i = 0; i < n; i++)
        printf("%d ", answer[i]);
    printf("\n");
}
