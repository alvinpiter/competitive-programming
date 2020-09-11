#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 100000

int N, numF;
LL tree[4 * MAXN + 3];
vector<int> uniqF;
vector<pair<pair<int, int>, int> > people;

void update(int node, int l, int r, int idx, LL val) {
    if (r < idx || l > idx)
        return;

    if (l == r) {
        tree[node] = max(tree[node], val);
        return;
    }

    int m = (l + r)/2;
    update(2 * node, l, m, idx, val);
    update(2 * node + 1, m + 1, r, idx, val);

    tree[node] = max(tree[2 * node], tree[2 * node + 1]);
}

LL query(int node, int l, int r, int le, int ri) {
    if (r < le || l > ri)
        return 0;

    if (l >= le && r <= ri)
        return tree[node];

    int m = (l + r)/2;
    return max(
        query(2 * node, l, m, le, ri),
        query(2 * node + 1, m + 1, r, le, ri)
    );
}

int getCompressedIndex(int f) {
    return (lower_bound(uniqF.begin(), uniqF.end(), f) - uniqF.begin()) + 1;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int b, f, d;
        scanf("%d%d%d", &b, &f, &d);

        people.push_back({{b, f}, d});
        uniqF.push_back(f);
    }

    sort(people.begin(), people.end());

    sort(uniqF.begin(), uniqF.end());
    uniqF.resize(distance(uniqF.begin(), unique(uniqF.begin(), uniqF.end())));

    numF = (int) uniqF.size();

    memset(tree, 0, sizeof(tree));

    vector<pair<int, LL> > pendingUpdate;

    LL maxi = 0;
    for (int i = 0; i < N; ) {
        pendingUpdate.clear();

        int j;
        LL sumCons = 0;
        for (j = i; j < N && people[j].first.first == people[i].first.first; j++) {
            if (people[j].first != people[j - 1].first)
                sumCons = people[j].second;
            else
                sumCons += people[j].second;

            int idx = getCompressedIndex(people[j].first.second);
            LL score = sumCons + query(1, 1, numF, 1, idx - 1);

            maxi = max(maxi, score);

            pendingUpdate.push_back({idx, score});
        }

        for (auto pu: pendingUpdate)
            update(1, 1, numF, pu.first, pu.second);

        i = j;
    }

    printf("%lld\n", maxi);
}
