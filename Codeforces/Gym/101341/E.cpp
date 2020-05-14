#include<bits/stdc++.h>
using namespace std;
#define LL long long int
#define MAXN 200000

int main() {
    int n, m;
    int teleport[MAXN + 3], bonus[MAXN + 3];

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        cin >> teleport[i];

    for (int i = 0; i < m; i++)
        cin >> bonus[i];

    LL answer = 0;

    //if there is bonus to the left of leftmost teleport
    if (bonus[0] < teleport[0])
        answer += (LL) 2 * (teleport[0] - bonus[0]);

    //If there is bonus to the right of rightmost teleport
    if (bonus[m - 1] > teleport[n - 1])
        answer += (LL) 2 * (bonus[m - 1] - teleport[n - 1]);

    //Process all the bonuses between two adjacent teleports
    for (int i = 0; i < n - 1; i++) {
        int l = lower_bound(bonus, bonus + m, teleport[i]) - bonus;
        int r = lower_bound(bonus, bonus + m, teleport[i + 1]) - bonus;

        if (bonus[l] == teleport[i])
            l += 1;

        if (r == m || bonus[r] >= teleport[i + 1])
            r -= 1;

        if (l > r)
            continue;

        LL mini = teleport[i + 1] - teleport[i];

        //All bonuses taken from current teleport
        mini = min(mini, (LL) 2 * (bonus[r] - teleport[i]));

        //All bonuses taken from next teleport
        mini = min(mini, (LL) 2 * (teleport[i + 1] - bonus[l]));

        //Find border t where all bonuses with indices <= t will be taken from current teleport
        for (int t = l; t < r; t++) {
            LL cost1 = 2 * (bonus[t] - teleport[i]);
            LL cost2 = 2 * (teleport[i + 1] - bonus[t + 1]);

            mini = min(mini, cost1 + cost2);
        }

        answer += mini;
    }

    cout << answer << endl;
}
