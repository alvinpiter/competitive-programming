#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, cost;
    string str;

    cin >> n >> k >> str;

    queue<string> Q;
    set<string> S;

    Q.push(str);
    S.insert(str);
    k -= 1;

    cost = 0;
    while (!Q.empty() && k > 0) {
        string u = Q.front(); Q.pop();

        for (int i = 0; i < u.length() && k > 0; i++) {
            string prefix = u.substr(0, i);
            string suffix = u.substr(i + 1);
            string v = prefix + suffix;

            if (S.find(v) == S.end()) {
                Q.push(v);
                S.insert(v);

                cost += (n - v.length());

                k--;
            }
        }
    }

    if (k > 0)
        cout << -1 << endl;
    else
        cout << cost << endl;
}
