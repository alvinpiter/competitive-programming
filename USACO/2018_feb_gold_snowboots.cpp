#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

/*
For shoes i, we can reach tile N if there is no di consectitve tiles whose snow's depth is > si.
We can process the shoes from the one with smallest si and update the state of our tiles (maintaining largest gap).
*/

int N, B, answer[MAXN + 3];
vector<pair<pair<int, int>, int> > shoes;
vector<pair<int, int> > tiles;
set<int> pos;
multiset<int> segmentLengths;

int main() {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
    
    scanf("%d%d", &N, &B);
    for (int i = 0; i < N; i++) {
        int f;
        scanf("%d", &f);

        tiles.push_back({f, i});
    }

    for (int i = 0; i < B; i++) {
        int s, d;
        scanf("%d%d", &s, &d);

        shoes.push_back({{s, d}, i});
    }

    sort(tiles.begin(), tiles.end());
    sort(shoes.begin(), shoes.end());

    pos.insert(-1);
    pos.insert(N);
    segmentLengths.insert(N);

    int ptrTiles = 0;
    for (int i = 0; i < B; i++) {
        while (ptrTiles < N && shoes[i].first.first >= tiles[ptrTiles].first) {
            int p = tiles[ptrTiles].second;

            auto lb = pos.lower_bound(p);
            int r = *lb;
            int l = *(--lb);

            segmentLengths.erase(segmentLengths.find(r - l - 1));
            segmentLengths.insert(p - l - 1);
            segmentLengths.insert(r - p - 1);

            pos.insert(p);

            ptrTiles += 1;
        }

        answer[shoes[i].second] = (*(--segmentLengths.end()) < shoes[i].first.second);
    }

    for (int i = 0; i < B; i++)
        printf("%d\n", answer[i]);
}
