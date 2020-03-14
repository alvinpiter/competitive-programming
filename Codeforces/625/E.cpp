#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000
#define LL long long int

int N, M, P, armorDefs[MAXN + 3];
pair<int, int> weapons[MAXN + 3], armors[MAXN + 3];
pair<int, pair<int, int> > monsters[MAXN + 3];
LL answer;

/*
Segment tree will support two queries:
* Increase all numbers in range l to r
* Get maximum number in range l to r
*/
LL tree[4 * MAXN + 3], lazy[4 * MAXN + 3];

LL evaluate(int node) {
    return tree[node] + lazy[node];
}

void pushDown(int node, int l, int r) {
    if (l != r) {
        lazy[2 * node] += lazy[node];
        lazy[2 * node + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void pullUp(int node) {
    tree[node] = max(evaluate(2 * node), evaluate(2 * node + 1));
}

void update(int node, int l, int r, int le, int ri, int val) {
    if (r < le || l > ri) {
        return;
    }

    if (l >= le && r <= ri) {
        lazy[node] += val;
        return;
    }

    pushDown(node, l, r);

    int m = (l + r)/2;
    update(2 * node, l, m, le, ri, val);
    update(2 * node + 1, m + 1, r, le, ri, val);

    pullUp(node);
}

int main() {
    scanf("%d%d%d", &N, &M, &P);

    for (int i = 1; i <= N; i++)
        scanf("%d%d", &weapons[i].first, &weapons[i].second);

    for (int i = 1; i <= M; i++)
        scanf("%d%d", &armors[i].first, &armors[i].second);

    for (int i = 1; i <= P; i++)
        scanf("%d%d%d", &monsters[i].first, &monsters[i].second.first, &monsters[i].second.second);

    sort(weapons + 1, weapons + N + 1);

    sort(armors + 1, armors + M + 1);
    for (int i = 1; i <= M; i++) armorDefs[i] = armors[i].first;

    sort(monsters + 1, monsters + P + 1);

    //Initialize segment tree
    memset(tree, 0, sizeof(tree));
    for (int i = 1; i <= M; i++)
        update(1, 1, M, i, i, -armors[i].second);

    int ptrMonster = 1;
    answer = -1e18;
    for (int i = 1; i <= N; i++) {
        //Add all monster whose defense is smaller than current weapon's attack
        while (ptrMonster <= P && monsters[ptrMonster].first < weapons[i].first) {
            //Find the suffix index that need to be updated
            int pos = lower_bound(armorDefs + 1, armorDefs + M + 1, monsters[ptrMonster].second.first + 1) - armorDefs;
            update(1, 1, M, pos, M, monsters[ptrMonster].second.second);

            ptrMonster += 1;
        }

        answer = max(answer, -weapons[i].second + evaluate(1));
    }

    printf("%lld\n", answer);
}
