#include<bits/stdc++.h>
using namespace std;
#define MAXN 100000

int N, M, who[MAXN + 3], ans[MAXN + 3], cnt;
int f[MAXN + 3], s[MAXN + 3];

//advance curr's choice, if currently he choose cereal
void advance(int curr, int cereal) {
    if (s[curr] == cereal) {
        //If cereal is his second choice, curr get nothing
        cnt -= 1;
        return;
    } else {
        //If cereal is his first choice

        if (who[s[curr]] == -1) {
            //his second choice has not been taken by someone else
            who[s[curr]] = curr;
            return;
        } else {
            if (who[s[curr]] < curr) {
                //his second choice has been taken by someone before him, curr get nothing
                cnt -= 1;
                return;
            } else {
                int nxt = who[s[curr]];

                who[s[curr]] = curr;
                advance(nxt, s[curr]);
            }
        }
    }
}

int main() {
    freopen("cereal.in", "r", stdin);
    freopen("cereal.out", "w", stdout);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> f[i] >> s[i];

    cnt = 0;
    memset(who, -1, sizeof(who));

    for (int i = N; i >= 1; i--) {
        int nxt = who[f[i]];

        cnt += 1;
        who[f[i]] = i;

        if (nxt != -1)
            advance(nxt, f[i]);

        ans[i] = cnt;
    }

    for (int i = 1; i <= N; i++)
        cout << ans[i] << endl;
}
