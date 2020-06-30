#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 1000
#define MAXS 20000

/*
Let's say the order of the blocks is already defined. We can apply dynamic programming:
dp[i][s] -> maximum achievable value if we consider blocks i..N and currently has solidness s

There are two transitions:
* Skip current block -> we go to state dp[i + 1][s]
* Take current block -> we go to state dp[i + 1][min(s - block weight), (block solidness)] and get current block's value

Now what's left is how to order the blocks. We sort the blocks based on largest (solidness + weight).
With this order, we try to maximize the left over solidness (min(s - block weight), (block solidness)).
*/

struct Block {
    int weight, solidness, value;
    Block() {}
    Block(int _w, int _s, int _v): weight(_w), solidness(_s), value(_v) {}
    bool operator<(Block other) const {
        return weight + solidness > other.weight + other.solidness;
    }
};

int N;
Block blocks[MAXN + 3];
LL dp[MAXN + 3][MAXS + 3];

LL solve(int idx, int s) {
    if (idx == N + 1)
        return 0;

    if (dp[idx][s] != -1)
        return dp[idx][s];

    LL skip = solve(idx + 1, s);
    LL take = 0;

    if (s >= blocks[idx].weight) {
        take = solve(idx + 1, min(s - blocks[idx].weight, blocks[idx].solidness)) + (LL) blocks[idx].value;
    }

    return dp[idx][s] = max(skip, take);
}

int main() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int w, s, v;
        cin >> w >> s >> v;

        blocks[i] = Block(w, s, v);
    }

    sort(blocks + 1, blocks + N + 1);

    memset(dp, -1, sizeof(dp));

    cout << solve(1, MAXS) << endl;
}
