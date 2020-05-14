#include<bits/stdc++.h>
using namespace std;
#define MAXN 200000

int main() {
    int n, m, cnt[MAXN + 3]; //cnt[i] = how many prefixes I_love_ for string i
    string names[MAXN + 3];

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> names[i];
    }

    cin >> m;

    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;

        cnt[a] = 1 + cnt[b];
        names[a] = names[b];
    }

    for (int rep = 1; rep <= cnt[1]; rep++)
        cout << "I_love_";
    cout << names[1] << endl;
}
