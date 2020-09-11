#include<bits/stdc++.h>
using namespace std;
#define MAXK 4
#define DEBUG true

/*
Convert each problem into a binary number that represents which team knows this problem.

Observation: There is no point taking two problems whose set of teams that knows them are the same.

There will be at most 2^k different problems to be considered. Just generate all the subset and check if it's valid.
*/

int main() {
    int n, k;
    bool seen[(1 << MAXK) + 3];
    vector<int> problems;

    scanf("%d%d", &n, &k);

    memset(seen, false, sizeof(seen));
    for (int i = 1; i <= n; i++) {
        int bin = 0, bit;
        for (int j = 0; j < k; j++) {
            scanf("%d", &bit);
            bin |= (bit << j);
        }

        if (!seen[bin]) {
            seen[bin] = true;
            problems.push_back(bin);
        }
    }

    int numProblem = (int) problems.size();
    for (int mask = 1; mask < (1 << numProblem); mask++) {
        int numTakenProblem = 0;
        int cnt[MAXK + 3]; //cnt[i] -> how many taken problem known by team i

        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < numProblem; i++) {
            if (mask & (1 << i)) {
                numTakenProblem += 1;

                //Find out which team knows this problem
                for (int j = 0; j < k; j++) {
                    if (problems[i] & (1 << j))
                        cnt[j] += 1;
                }
            }
        }

        bool valid = true;
        for (int i = 0; i < k; i++) {
            if (cnt[i] * 2 > numTakenProblem)
                valid = false;
        }

        if (valid) {
            printf("YES\n");
            return 0;
        }
    }

    printf("NO\n");
}
