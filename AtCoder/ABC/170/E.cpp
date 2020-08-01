#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int N, Q, rat[MAXN + 3], pos[MAXN + 3];
multiset<int> kindergarten[MAXN + 3];
multiset<int> maxis;

void eraseFrom(int k, int rating) {
    int maxi = *(--kindergarten[k].end());

    kindergarten[k].erase(kindergarten[k].find(rating));

    if (rating >= maxi) {
        maxis.erase(maxis.find(rating));

        if (!kindergarten[k].empty()) {
            int newMaxi = *(--kindergarten[k].end());
            maxis.insert(newMaxi);
        }
    }
}

void insertTo(int k, int rating) {
    if (kindergarten[k].empty()) {
        maxis.insert(rating);
        kindergarten[k].insert(rating);
    } else {
        int maxi = *(--kindergarten[k].end());

        kindergarten[k].insert(rating);

        if (rating >= maxi) {
            maxis.erase(maxis.find(maxi));

            int newMaxi = *(--kindergarten[k].end());
            maxis.insert(newMaxi);
        }
    }
}

int main() {
    scanf("%d%d", &N, &Q);
    for (int i = 1; i <= N; i++) {
        scanf("%d%d", &rat[i], &pos[i]);
        insertTo(pos[i], rat[i]);
    }

    for (int i = 1; i <= Q; i++) {
        int C, D;
        scanf("%d%d", &C, &D);

        eraseFrom(pos[C], rat[C]);
        insertTo(D, rat[C]);

        pos[C] = D;

        printf("%d\n", *maxis.begin());
    }
}
