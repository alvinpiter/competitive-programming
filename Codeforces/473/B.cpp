#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, m, a[100003], temp[100003];
    string s;
    map<string, int> wordIndex;

    cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s;

        wordIndex[s] = i;
    }

    for (int i = 1; i <= n; i++)
        cin >> a[i];

    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;

        int mini = 1e9;
        for (int j = 1; j <= x; j++) {
            cin >> temp[j];
            mini = min(mini, a[temp[j]]);
        }

        for (int j = 1; j <= x; j++)
            a[temp[j]] = mini;
    }

    long long int cost = 0;
    for (int i = 1; i <= m; i++) {
        cin >> s;
        cost += a[wordIndex[s]];
    }

    cout << cost << endl;
}
