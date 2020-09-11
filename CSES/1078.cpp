#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MOD 1000000007
#define MAXN 2000000

LL fact[MAXN + 3];

LL fastExponentiation(LL base, int p) {
    if (p == 0)
        return 1;

    LL half = fastExponentiation(base, p/2);
    LL halfhalf = (half * half)%MOD;

    if (p%2 == 0)
        return halfhalf;
    else
        return (halfhalf * base)%MOD;
}

LL C(int n, int k) {
    LL numerator = fact[n];
    LL denominator = (fact[k] * fact[n - k])%MOD;
    return (numerator * fastExponentiation(denominator, MOD - 2))%MOD;
}


//Solve the problem for given grid size nxm and blocks.
LL solve(int n, int m, vector<pair<int, int> >& blocks) {
    fact[0] = 1;
    for (int i = 1; i <= MAXN; i++)
        fact[i] = (fact[i - 1] * i)%MOD;

    blocks.push_back({n, m});

    sort(blocks.begin(), blocks.end()); //sort in non-decreasing order of row and if tie by increasing order of column

    int k = (int) blocks.size();
    LL dp[k + 3]; //dp[i] = number of ways to go from (1, 1) to i-th block.

    //Initially we pretend there are no blocks.
    for (int i = 0; i < k; i++)
        dp[i] = C(blocks[i].first + blocks[i].second - 2, blocks[i].first - 1);

    //We add blocks one by one and update dp of affected blocks (ones on the right and down)
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            if (i == j)
                continue;

            if (blocks[j].first >= blocks[i].first && blocks[j].second >= blocks[i].second) {
                int dr = blocks[j].first - blocks[i].first;
                int dc = blocks[j].second - blocks[i].second;


                //Number of ways to go to j decreased by number of ways to go to j that goes through i.
                LL ij = (dp[i] * C(dr + dc, dr)%MOD)%MOD;
                dp[j] = (dp[j] - ij + MOD)%MOD;
            }
        }
    }

    return dp[k - 1];
}

int main() {
    int n, k;

    cin >> n >> k;

    vector<pair<int, int> > blocks;
    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;

        blocks.push_back({r, c});
    }

    cout << solve(n, n, blocks) << endl;
}
