#include<bits/stdc++.h>
using namespace std;
#define MAXN 1000000

/*
open[i] = index of opening bracket for closing bracket i
dp[i] = length of longest bracket sequence that ends at i
*/

string s;
int n, open[MAXN + 3], dp[MAXN + 3];

int main() {
    cin >> s;

    n = (int) s.length();

    memset(open, -1, sizeof(open));
    memset(dp, 0, sizeof(dp));

    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            st.push(i);
        else {
            if (st.empty() || s[st.top()] != '(')
                continue;
            else {
                open[i] = st.top();
                st.pop();
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == '(' || open[i] == -1)
            continue;

        int prv = open[i] - 1;
        dp[i] = (i - prv) + (prv == 0 ? 0 : dp[prv]);
    }

    int best = 0;
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        if (dp[i] > best) {
            best = dp[i];
            cnt = 1;
        } else if (dp[i] == best) {
            cnt += 1;
        }
    }

    if (best == 0)
        cout << "0 1\n";
    else
        cout << best << " " << cnt << endl;
}
