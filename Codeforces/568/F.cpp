#include<bits/stdc++.h>
using namespace std;

/*
Categorize friend by its set of favorite ingredients. There will be at most 2^9 different friends.
Do similar thing with pizza.
*/

int n, m, cntFriend[1024], happy[1024][1024]; //happy[i][j] -> 1 if friend with category i is happy with pizza with category j
vector<pair<int, int> > pizza[1024]; //{price, index}

int isHappy(int f, int p) {
    if (happy[f][p] != -1)
        return happy[f][p];

    happy[f][p] = 1;
    for (int i = 0; i < 9; i++) {
        if ((f&(1 << i)) > 0 && (p&(1 << i)) == 0)
            happy[f][p] = 0;
    }

    return happy[f][p];
}

int main() {
    scanf("%d%d", &n, &m);

    memset(cntFriend, 0, sizeof(cntFriend));
    for (int i = 0; i < n; i++) {
        int f, b, category = 0;

        scanf("%d", &f);
        for (int j = 0; j < f; j++) {
            scanf("%d", &b);
            category |= (1 << (b - 1));
        }

        cntFriend[category] += 1;
    }

    for (int i = 0; i < m; i++) {
        int c, r, a, category = 0;

        scanf("%d%d", &c, &r);
        for (int j = 0; j < r; j++) {
            scanf("%d", &a);
            category |= (1 << (a - 1));
        }

        pizza[category].push_back({c, i + 1});
    }

    for (int p = 0; p < (1 << 9); p++) {
        sort(pizza[p].begin(), pizza[p].end());
    }

    memset(happy, -1, sizeof(happy));

    int maxHappy = 0;
    int minPrice = 2e9 + 1;
    pair<int, int> bestIndices;

    //Buy 2 pizzas from same category
    for (int p = 0; p < (1 << 9); p++) {
        if (pizza[p].size() < 2)
            continue;

        int cntHappy = 0;
        int price = pizza[p][0].first + pizza[p][1].first;

        for (int f = 0; f < (1 << 9); f++) {
            if (isHappy(f, p) == 1)
                cntHappy += cntFriend[f];
        }

        if (cntHappy > maxHappy || (cntHappy == maxHappy && price < minPrice)) {
            maxHappy = cntHappy;
            minPrice = price;
            bestIndices = make_pair(pizza[p][0].second, pizza[p][1].second);
        }
    }

    //Buy 2 pizzas from different category
    for (int p1 = 0; p1 < (1 << 9); p1++) {
        if (pizza[p1].empty())
            continue;

        for (int p2 = p1 + 1; p2 < (1 << 9); p2++) {
            if (pizza[p2].empty())
                continue;

            int cntHappy = 0;
            int price = pizza[p1][0].first + pizza[p2][0].first;

            for (int f = 0; f < (1 << 9); f++) {
                if (isHappy(f, p1 | p2))
                    cntHappy += cntFriend[f];
            }

            if (cntHappy > maxHappy || (cntHappy == maxHappy && price < minPrice)) {
                maxHappy = cntHappy;
                minPrice = price;
                bestIndices = make_pair(pizza[p1][0].second, pizza[p2][0].second);
            }
        }
    }

    printf("%d %d\n", bestIndices.first, bestIndices.second);
}
