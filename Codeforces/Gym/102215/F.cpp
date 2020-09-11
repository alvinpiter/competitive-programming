#include<bits/stdc++.h>
using namespace std;
#define INF 1000000000
#define MAXN 300000
#define MAXLG 19

/*
Sort the creatures, lowest hp first.
Let's take a look at i-th creature. We find the creature j which can be defeated by i and among all of them, pick the one with maximum attack.
We can do this by binary search (since hp is sorted) and range max query.
*/

struct Creature {
    int attack, hp, index;
    Creature(int _attack, int _hp, int _index): attack(_attack), hp(_hp), index(_index) {}
};

bool cmpHp(Creature a, Creature b) {
    return a.hp < b.hp;
}

int n;
int dp[MAXN + 3][MAXLG + 3]; //for rmq
vector<Creature> creatures;

//Get max attack in range l..r
int getMax(int l, int r) {
    if (l > r)
        return -INF;

    int curr = l;
    int maxi = creatures[l].attack;
    for (int lg = 0; lg <= MAXLG; lg++) {
        if ((r - l)&(1 << lg)) {
            maxi = max(maxi, dp[curr][lg]);
            curr += (1 << lg);
        }
    }

    return maxi;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, h;
        scanf("%d%d", &a, &h);

        creatures.push_back(Creature(a, h, i));
    }

    sort(creatures.begin(), creatures.end(), cmpHp);

    //Init rmq dp
    for (int i = 0; i < n; i++) {
        dp[i][0] = (i == n - 1 ? creatures[i].attack : max(creatures[i].attack, creatures[i + 1].attack));
    }

    for (int lg = 1; lg <= MAXLG; lg++) {
        for (int i = 0; i < n; i++) {
            dp[i][lg] = dp[i][lg - 1];

            int nxt = (i + (1 << (lg - 1)));
            if (nxt < n)
                dp[i][lg] = max(dp[i][lg], dp[nxt][lg - 1]);
        }
    }

    int bestDecrease = 0;
    int bestIdx; //index of first best creature to choose
    for (int i = 0; i < n; i++) {
        //find the last creature this creature can defeat
        int lo = 0, hi = n - 1, mid;
        while (hi >= lo) {
            mid = (lo + hi)/2;
            if (creatures[mid].hp <= creatures[i].attack)
                lo = mid + 1;
            else
                hi = mid - 1;
        }

        if (hi == -1)
            continue;

        int lastIdx = hi;
        int maxAttack;

        if (lastIdx < i) {
            maxAttack = getMax(0, lastIdx);
        } else {
            maxAttack = max(getMax(0, i - 1), getMax(i + 1, lastIdx));
        }

        int decrease = maxAttack + (maxAttack >= creatures[i].hp ? creatures[i].attack : 0);

        if (decrease > bestDecrease) {
            bestDecrease = decrease;
            bestIdx = i;
        }
    }

    printf("%d\n", bestDecrease);
    if (bestDecrease == 0) {
        printf("1 2\n");
    } else {
        //These lines of codes can be avoided if our getMax method returns an index instead of a value.
        for (int i = 0; i < n; i++) {
            if (i == bestIdx)
                continue;

            int decrease = 0;
            decrease += (creatures[bestIdx].attack >= creatures[i].hp ? creatures[i].attack : 0);
            decrease += (creatures[i].attack >= creatures[bestIdx].hp ? creatures[bestIdx].attack : 0);

            if (decrease == bestDecrease) {
                printf("%d %d\n", creatures[bestIdx].index + 1, creatures[i].index + 1);
                return 0;
            }
        }
    }
}
